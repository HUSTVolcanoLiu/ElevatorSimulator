//WARNING:增删人与设置尾部（目标楼层为0）和遍历链表的操作已经转移到楼层与电梯类
//        仅保留了目标楼层，所有的信号由楼层与电梯类发出
//该类为人员的链表，在楼层与电梯类中被使用

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#pragma execution_character_set("utf-8")

#include <QObject>

class LinkedList : public QObject
{
    Q_OBJECT
public:
    explicit LinkedList(QObject *parent = nullptr);

    void setTargetFloor(int target);               //修改目标楼层以及上下楼信息
    int getTargetFloor();

    class LinkedList* next;        //队列中的后一个人
    class LinkedList* prev;        //队列中的前一个人

signals:

public slots:

private:
    int targetFloor;         //目标楼层
};

#endif // LINKEDLIST_H
