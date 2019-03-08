#include "elevatorclass.h"

ElevatorClass::ElevatorClass(QObject *parent) : QObject(parent)
{

}

int ElevatorClass::getFloor()
{
    return this->floor;
}

void ElevatorClass::setFloor(int newFloor)
{
    this->floor = newFloor;
}

int ElevatorClass::getStatus()
{
    return this->status;
}

void ElevatorClass::setStatus(int newStatus)
{
    this->status = newStatus;
}

int ElevatorClass::calcDistance()
{
    int newDistance = 0;
    if(this->command.count() == 0) { return 0; }
    else
    {
        for(int i = 0; i < this->command.count(); i++)
        {
            if(i == 0) { newDistance += abs(command[i] - floor); }
            else { newDistance += abs(command[i] - command[i - 1]); }
        }
    }
    this->distance = newDistance;
    return newDistance;
}

int ElevatorClass::calcDistance(int index)
{
    int newDistance = 0;
    if(this->command.count() == 0) { return 0; }
    else
    {
        for(int i = 0; i < this->command.count() && i < index + 1; i++)
        {
            if(i == 0) { newDistance += abs(command[i] - floor); }
            else { newDistance += abs(command[i] - command[i - 1]); }
        }
    }
    return newDistance;
}

int ElevatorClass::getSteps()
{
    return this->steps;
}

void ElevatorClass::addSteps()
{
    this->steps++;
}

void ElevatorClass::resetSteps()
{
    this->steps = 0;
}

bool ElevatorClass::getLoad()
{
    return this->load;
}

void ElevatorClass::enableLoad()
{
    emit signalSendLoad();
    this->load = 1;
}

void ElevatorClass::disableLoad()
{
    emit signalSendLoad();
    this->load = 0;
}
