#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QtGlobal>
#include <elevatorclass.h>
#include <floorclass.h>

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    void setTimeStep(int t);
    int generateRandomFloor();//生成楼层随机数
    bool generateProbability(int r);     //按概率生成人

    int loadPeople(ElevatorClass* toElevator);                  //从楼层装载人
    int releasePeople(ElevatorClass* fromElevator);             //从电梯释放人
    void calcGrade_addCommand(int fromFloor,int target);      //计算加权并添加指令

    class ElevatorClass* elevatorClass[3];
    class FloorClass* floorClass[12];

    QTimer* timer;                      //计时器
    long long steps = 0;                //从开始的步数
    int timeStep = 1;                //timeStep为现实中的200ms

    int count = 50, distance = 50;

signals:
    void signalStepAdd(int step);
    void signalStepAdd(QString);        //发送时间信号
    void signalRelease();
    void signalGenerate();

public slots:
    void slotStepAdd();                 //增加步数
    void slotStepRun();                 //控制三部电梯
    void slotCommand();
    void slotAddSpeed();
    void slotDecSpeed();
    void slotFlushValue(int, int);

private:
    //电梯的各种参数
    int runTime = 6;                   //运行时间为1s default:6
    int peopleTime = 2;                 //进出时间为0.5s default:2

    //乘客的各种参数
    int ratio = 12;                    //生成率
};

#endif // CORE_H
