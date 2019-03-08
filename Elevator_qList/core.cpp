#include "core.h"
#include <QDebug>

Core::Core(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    timer->setTimerType(Qt::PreciseTimer);
    timer->setInterval(timeStep);
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);

//初始化电梯和楼层
    for(int i = 0; i < 3; i++)
    {
        elevatorClass[i] = new ElevatorClass;
    }
    for(int i = 0; i < 12; i++)
    {
        floorClass[i] = new FloorClass;
    }

    connect(timer,SIGNAL(timeout()),this,SLOT(slotStepAdd())); //每触发一次计时器步数增加一
    connect(timer,SIGNAL(timeout()),this,SLOT(slotStepRun()));
    connect(timer,SIGNAL(timeout()),this,SLOT(slotCommand()));

}

void Core::setTimeStep(int s)
{
    this->timeStep = s;
}

int Core::generateRandomFloor()
{
    int temp;
    do{
        qrand();
        //qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
        temp = qrand() % 13;
    }while(temp == 0);
    return temp;
}

bool Core::generateProbability(int r)
{
    int temp;
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    temp = qrand() % r;
    return temp == 0 ? 1 : 0;
}


//slots
void Core::slotStepRun()
{
    for(int i = 0; i < 3; i++)
    {
        if(elevatorClass[i]->getLoad() == false)    //若电梯不是进出状态
        {
            switch (elevatorClass[i]->getStatus()) {
            case -1:
                if(elevatorClass[i]->getSteps() == runTime)
                {
                    elevatorClass[i]->setFloor(elevatorClass[i]->getFloor() - 1);
                    elevatorClass[i]->resetSteps();
                    if(elevatorClass[i]->people.indexOf(elevatorClass[i]->getFloor()) != -1)     //若有人出电梯
                    {
                        elevatorClass[i]->enableLoad();
                    }
                    if(elevatorClass[i]->getFloor() == elevatorClass[i]->command[0])    //若到达命令楼层
                    {
                        elevatorClass[i]->command.removeFirst();
                        elevatorClass[i]->enableLoad();
                        if(elevatorClass[i]->command.isEmpty())
                        {
                            elevatorClass[i]->setStatus(0);
                        }
                        else
                        {
                            elevatorClass[i]->setStatus(elevatorClass[i]->command[0] > elevatorClass[i]->getFloor() ? 1 : -1);
                        }
                    }
                    //补救措施
                    if(elevatorClass[i]->getFloor() < 1)
                    {
                        elevatorClass[i]->setFloor(1);
                        elevatorClass[i]->setStatus(1);
                    }
                }
                else
                {
                    elevatorClass[i]->addSteps();
                }
                break;
            case 1:
                if(elevatorClass[i]->getSteps() == runTime)
                {
                    elevatorClass[i]->setFloor(elevatorClass[i]->getFloor() + 1);
                    elevatorClass[i]->resetSteps();
                    if(elevatorClass[i]->people.indexOf(elevatorClass[i]->getFloor()) != -1)     //若有人出电梯
                    {
                        elevatorClass[i]->enableLoad();
                    }
                    if(elevatorClass[i]->getFloor() == elevatorClass[i]->command[0])    //若到达命令楼层
                    {
                        elevatorClass[i]->command.removeFirst();
                        elevatorClass[i]->enableLoad();
                        if(elevatorClass[i]->command.isEmpty())
                        {
                            elevatorClass[i]->setStatus(0);
                        }
                        else
                        {
                            elevatorClass[i]->setStatus(elevatorClass[i]->command[0] > elevatorClass[i]->getFloor() ? 1 : -1);
                        }
                    }
                    //补救措施
                    if(elevatorClass[i]->getFloor() > 12)
                    {
                        elevatorClass[i]->setFloor(12);
                        elevatorClass[i]->setStatus(-1);
                    }
                }
                else
                {
                    elevatorClass[i]->addSteps();
                }
                break;
            case 0:
                if(elevatorClass[i]->command.isEmpty() == 0)
                {
                    if(elevatorClass[i]->command[0] == elevatorClass[i]->getFloor())
                    {
                        elevatorClass[i]->enableLoad();
                    }
                    else
                    {
                        elevatorClass[i]->setStatus(elevatorClass[i]->command[0] > elevatorClass[i]->getFloor() ? 1 : -1);
                    }
                }
                break;
            default:
                //qDebug() << "default";
                break;
            }
        }
        else    //若电梯是进出状态
        {
            if(elevatorClass[i]->getSteps() == peopleTime)
            {
                elevatorClass[i]->resetSteps();
                if(releasePeople(elevatorClass[i]))
                {
                    return;
                }
                if(loadPeople(elevatorClass[i]))
                {
                    return;
                }
                elevatorClass[i]->disableLoad();
            }
            else
            {
                elevatorClass[i]->addSteps();
            }
        }
        //补救措施
        if(elevatorClass[i]->command.size() && elevatorClass[i]->getStatus() == 0)
        {
            if(elevatorClass[i]->command[0] == elevatorClass[i]->getFloor())
            {
                elevatorClass[i]->command.removeFirst();
            }
        }
    }
    //qDebug() << "steps" << elevatorClass[0]->getSteps() << "status" << elevatorClass[0]->getStatus() << "load" << elevatorClass[0]->getLoad() << "floor" << elevatorClass[0]->getFloor() << "commondSize" << elevatorClass[0]->command.size() << "peopleSize" << elevatorClass[0]->people.size();
}

void Core::slotStepAdd()
{
    steps++;
    emit signalStepAdd(QString::number(steps/5));             //时间增加发出信号

    //debug
    for(int i = 0; i < elevatorClass[0]->command.size(); i++)
    {
        //qDebug() << elevatorClass[0]->command[i];
    }
    //qDebug() << count;
}

void Core::slotCommand()
{
    //是否生成乘客，生成乘客后安排电梯队列
    if(generateProbability(ratio))
    {
        int f;      //乘客楼层
        int t;      //目标楼层
        f = generateRandomFloor();
        do{
             t = generateRandomFloor();
        } while(t == f);
        floorClass[f - 1]->people.append(t);
        qDebug() << "generate a person" << "from" << f << "to" << t;
        emit signalGenerate();
        calcGrade_addCommand(f, t);
    }
}

void Core::slotDecSpeed()
{
    if(timeStep < 10)
    {
        timeStep++;
    }
    else if(timeStep <= 190)
    {
        timeStep += 10;
    }
    timer->setInterval(timeStep);
}

void Core::slotAddSpeed()
{
    if(timeStep == 1)
    {
        return;
    }
    if(timeStep < 11 && timeStep > 1)
    {
        timeStep--;
    }
    else
    {
        timeStep -= 10;
    }
    timer->setInterval(timeStep);
}

void Core::slotFlushValue(int c, int d)
{
    count = c;
    distance =d;
}

int Core::loadPeople(ElevatorClass* toElevator)
{
    if(toElevator->people.size() == 16) return 0;
    if(floorClass[toElevator->getFloor() - 1]->people.size() != 0)
    {
        if(toElevator->getStatus() == 0)
        {
            //若电梯静止，则上一个人，添加命令
            toElevator->people.append(floorClass[toElevator->getFloor() - 1]->people[0]);
            if(toElevator->command.indexOf(toElevator->people.last()) == -1)
            {
                toElevator->command.append(floorClass[toElevator->getFloor() - 1]->people[0]);
            }
            floorClass[toElevator->getFloor() - 1]->people.removeFirst();
            return 1;
        }
        else
        {
            //若电梯有方向，则载入与此电梯方向相同的人
            for(int i = 0; i < floorClass[toElevator->getFloor() - 1]->people.size(); i++)
            {
                if((floorClass[toElevator->getFloor() - 1]->people[i] - toElevator->getFloor()) * toElevator->getStatus() > 0)
                {
                    toElevator->people.append(floorClass[toElevator->getFloor() - 1]->people.takeAt(i));
                    if((toElevator->people.last() > toElevator->max || toElevator->people.last() < toElevator->min) && toElevator->command.indexOf(toElevator->people.last()) == -1)
                    {
                        toElevator->command.append(toElevator->people.last());
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Core::releasePeople(ElevatorClass* fromElevator)
{
    int i = fromElevator->people.indexOf(fromElevator->getFloor());
    if(i == -1)
    {
        return 0;
    }
    else
    {
        //qDebug() << "release";
        fromElevator->people.takeAt(i);
        emit signalRelease();
        return 1;
    }
}

void Core::calcGrade_addCommand(int fromFloor, int target)
{
    float grade[3];
    int count[3];
    int commandSize;
    int distance[3] = { -1, -1, -1};
    int index[3] = { 0, 0, 0 };
    int isUp = target > fromFloor ? 1 : -1;
    bool isInsert[3] = { 0, 0, 0 };
    bool alreadyTheSame[3] = {0, 0, 0};
    for(int n = 0; n < 3; n++)
    {
        count[n] = elevatorClass[n]->people.size();
        commandSize = elevatorClass[n]->command.size();
        //如果顺路
        if(commandSize == 0)    //若命令队列为空
        {
            index[n] = 0;
            distance[n] = abs(elevatorClass[n]->getFloor() - fromFloor);
        }
        else
        {
            for(index[n] = 0; index[n] < elevatorClass[n]->command.size(); index[n]++)
            {
                if(fromFloor == elevatorClass[n]->command[index[n]])        //若命令中有乘客楼层
                {
                    if(index[n] == elevatorClass[n]->command.size() - 1)    //若此命令在队尾
                    {
                        distance[n] = elevatorClass[n]->calcDistance();
                        alreadyTheSame[n] = 1;
                        break;
                    }
                    else                                                    //若此命令不在队尾
                    {
                        if(elevatorClass[n]->command[index[n] + 1] - elevatorClass[n]->command[index[n]] * isUp > 0)    //若方向相同
                        {
                            distance[n] = elevatorClass[n]->calcDistance(index[n]);
                            alreadyTheSame[n] = 1;
                            break;
                        }
                    }
                }
                else    //若命令中无乘客楼层
                {
                    if(index[n] == 0)
                    {
                        if(elevatorClass[n]->command[0] - elevatorClass[n]->getFloor() * isUp > 0)
                        {
                            distance[n] = elevatorClass[n]->calcDistance();
                            break;
                        }
                    }
                    else
                    {
                        if(elevatorClass[n]->command[index[n]] - elevatorClass[n]->command[index[n] - 1] * isUp > 0)
                        {
                            distance[n] = elevatorClass[n]->calcDistance(index[n] - 1);
                            isInsert[n] = 1;
                            alreadyTheSame[n] = 1;
                            break;
                        }
                    }
                }
            }
            if(distance[n] == -1)
            {
                distance[n] = elevatorClass[n]->calcDistance();
            }
        }
        grade[n] = this->distance * distance[n] + this->count * count[n];
    }
    int min = 0;
    for(int i = 1; i < 3; i++)
    {
        if(grade[i] < grade[i - 1])
        {
            min = i;
        }
    }
    if(!alreadyTheSame[min])
    {
        if(elevatorClass[min]->command.isEmpty())
        {
            elevatorClass[min]->command.append(fromFloor);
        }
        else if(isInsert[min])
        {
            elevatorClass[min]->command.insert(index[min], fromFloor);
        }
        else
        {
            elevatorClass[min]->command.append(fromFloor);
        }
    }
    elevatorClass[min]->min = *std::min_element(elevatorClass[min]->command.begin(),elevatorClass[min]->command.end());
    elevatorClass[min]->max = *std::max_element(elevatorClass[min]->command.begin(),elevatorClass[min]->command.end()); //重置命令中的最大值与最小值
}
