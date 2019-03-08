#ifndef ELEVATORCLASS_H
#define ELEVATORCLASS_H

#include <QObject>

class ElevatorClass : public QObject
{
    Q_OBJECT
public:
    explicit ElevatorClass(QObject *parent = nullptr);

    int getFloor();                 //得到电梯楼层
    void setFloor(int newFloor);    //设置电梯楼层
    int getStatus();                //得到电梯状态
    void setStatus(int newStatus);  //设置电梯状态

    int calcDistance();             //计算电梯总路程
    int calcDistance(int index);    //计算电梯到某索引的路程

    int getSteps();                 //得到步数
    void addSteps();                //步数自增
    void resetSteps();              //重置步数

    bool getLoad();
    void enableLoad();
    void disableLoad();

    //成员队列
    QList<int> people;
    QList<int> command;

    int min = 1, max = 1;

signals:
    void signalSendLoad();

public slots:

private:
    int floor = 1;
    int status = 0;
    int distance = 0;
    int steps = 0;
    bool load = 0;
};

#endif // ELEVATORCLASS_H
