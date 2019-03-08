#include "peoplelist.h"

PeopleList::PeopleList(QObject *parent) : QObject(parent)
{
    tail = new List;
    head = tail;
}

PeopleList::List::List(QObject *parent) : QObject(parent)//构造函数
{
    targetFloor = 0;    //目标楼层为0代表这是队尾
    isUp = 0;
    isTail = 1;
    next = nullptr;
    prev = nullptr;
}





void PeopleList::List::setisUp(bool isUp)
{
    this->isUp = isUp;
}

void PeopleList::List::setTargetFloor(int target)
{
    this->targetFloor = target;
}
