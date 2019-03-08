#include "elevator.h"
#include <QApplication>
#include <QTranslator>
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator tsor;           //创建翻译器
    tsor.load("C:/Users/Charles/Desktop/ElevatorSimulator/Elevator_qList/en.qm");    //加载语言包
    a.installTranslator(&tsor); //安装翻译器
    a.setFont(QFont("微软雅黑", 9, 50));
    Elevator w;
    w.show();

    return a.exec();
}
