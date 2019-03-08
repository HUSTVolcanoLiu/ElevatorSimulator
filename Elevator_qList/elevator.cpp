#include "elevator.h"

Elevator::Elevator(QWidget *parent)
    : QWidget(parent)
{
    core = new Core;
    HLayout = new QHBoxLayout;
    stateMonitor = new StateMonitor;
    floorState = new FloorState;
    totalFloor = new TotalFloor;
    for(int i = 0; i < 3; i++)
    {
        elevatorDisplayThread[i] = new ElevatorDisplayThread;
        elevatorDisplayThread[i]->UIsetElevatorPointer(totalFloor);
        elevatorDisplayThread[i]->setElevatorPointer(core->elevatorClass[i]);
        elevatorDisplayThread[i]->setFloorPointer(core->floorClass);
        elevatorDisplayThread[i]->num = i;
        connect(core->timer, SIGNAL(timeout()), elevatorDisplayThread[i], SLOT(slotFlushInfo()));
    }
    statusDisplayThread = new StatusDisplayThread;
    statusDisplayThread->UIsetElevatorPointer(totalFloor);
    statusDisplayThread->setElevatorPointer(core->elevatorClass);
    statusDisplayThread->setStateMoniterPointer(stateMonitor);
    statusDisplayThread->setCorePointer(core);
    statusDisplayThread->setFloorStatePointer(floorState);
    connect(core->elevatorClass[0], SIGNAL(signalSendLoad()), statusDisplayThread, SLOT(slotFlushInfo()));
    connect(core->elevatorClass[1], SIGNAL(signalSendLoad()), statusDisplayThread, SLOT(slotFlushInfo()));
    connect(core->elevatorClass[2], SIGNAL(signalSendLoad()), statusDisplayThread, SLOT(slotFlushInfo()));
    connect(core, SIGNAL(signalRelease()), statusDisplayThread, SLOT(slotAddCount()));
    connect(core, SIGNAL(signalGenerate()), statusDisplayThread, SLOT(slotGenerateCount()));

    this->setLayout(HLayout);
    this->setStyleSheet("background-color: rgb(0, 0, 0);");
    this->resize(600,450);

    HLayout->addWidget(stateMonitor);
    HLayout->addWidget(floorState);
    HLayout->addWidget(totalFloor);
    HLayout->setStretch(2,1);
    HLayout->setSpacing(0);
    HLayout->setMargin(0);

    core->timer->start();
    connect(core, SIGNAL(signalStepAdd(QString)), stateMonitor->lineRunTime, SLOT(setText(QString)));//信号连接，显示运行时间

    connect(stateMonitor->buttonSpeedup, SIGNAL(clicked()), core, SLOT(slotAddSpeed()));
    connect(stateMonitor->buttonSpeedup, SIGNAL(clicked()), this, SLOT(slotShowSpeed()));

    connect(stateMonitor->buttonSlowdown, SIGNAL(clicked()), core, SLOT(slotDecSpeed()));
    connect(stateMonitor->buttonSlowdown, SIGNAL(clicked()), this, SLOT(slotShowSpeed()));

    connect(floorState->settingWidget, SIGNAL(signalSendValue(int, int)), core, SLOT(slotFlushValue(int, int)));
}

Elevator::~Elevator()
{

}




ElevatorDisplayThread::ElevatorDisplayThread(QObject *parent) : QThread(parent)
{
    styleOrigin = "color: rgb(255, 255, 255); background-color: rgb(50, 50, 50);";
    styleRunning = "color: rgb(255, 255, 255); background-color: rgb(50, 200, 50);";
    stylePause = "color: rgb(255, 255, 255); background-color: rgb(210, 100, 0);";
    styleStop = "color: rgb(255, 255, 255); background-color: rgb(200, 0, 0);";
}

void ElevatorDisplayThread::UIsetElevatorPointer(TotalFloor* totFl)
{
    this->pTotalFloor = totFl;
}

void ElevatorDisplayThread::setElevatorPointer(ElevatorClass* elev)
{
        pElevatorClass = elev;
}

void ElevatorDisplayThread::setFloorPointer(FloorClass* floo[12])
{
    for(int i = 0; i < 12; i++)
    {
        pFloorClass[i] = floo[i];
    }
}

void ElevatorDisplayThread::slotFlushInfo()
{

    for(int j = 0; j < 12; j++)
    {
        if(pElevatorClass->getFloor() == j + 1)
        {
            if(pElevatorClass->getLoad() == 0)
            {
                //pTotalFloor->floorInfo[num]->floor[j]->setStyleSheet(styleRunning);
            }
            else
            {
                //pTotalFloor->floorInfo[num]->floor[j]->setStyleSheet(stylePause);
            }
            pTotalFloor->floorInfo[num]->floor[j]->setText(QString::number(pElevatorClass->people.size()));
        }
        else
        {
            //pTotalFloor->floorInfo[num]->floor[j]->setStyleSheet(styleOrigin);
            pTotalFloor->floorInfo[num]->floor[j]->setText("");
        }
    }

}

void Elevator::slotShowSpeed()
{
    stateMonitor->lineEmulation->setText(QString::number(core->timeStep));
}




StatusDisplayThread::StatusDisplayThread(QObject *parent) : QThread(parent)
{
    styleOrigin = "color: rgb(255, 255, 255); background-color: rgb(50, 50, 50); border-radius: 0px; font-size:30px;";
    styleRunning = "color: rgb(255, 255, 255); background-color: rgb(50, 200, 50); border-radius: 0px; font-size:30px;";
    stylePause = "color: rgb(255, 255, 255); background-color: rgb(210, 100, 0); border-radius: 0px; font-size:30px;";
}

void StatusDisplayThread::UIsetElevatorPointer(TotalFloor* totFl)
{
    this->pTotalFloor = totFl;
}

void StatusDisplayThread::setElevatorPointer(ElevatorClass* elev[3])
{
    for(int i = 0; i < 3; i++)
    {
        pElevatorClass[i] = elev[i];
    }
}

void StatusDisplayThread::setStateMoniterPointer(StateMonitor* statM)
{
    pStateMonitor = statM;
}

void StatusDisplayThread::setCorePointer(Core* co)
{
    pCore = co;
}

void StatusDisplayThread::setFloorStatePointer(FloorState* flo)
{
    pFloorState = flo;
}

void StatusDisplayThread::slotFlushInfo()
{
    for(int i = 0; i < 3; i++)
    {
        pTotalFloor->floorInfo[i]->controlElevator->setText(QString::number(pElevatorClass[i]->command.size()));
        if(pElevatorClass[i]->getLoad())
        {
            pTotalFloor->floorInfo[i]->controlElevator->setStyleSheet(stylePause);
        }
        else
        {
            pTotalFloor->floorInfo[i]->controlElevator->setStyleSheet(styleRunning);
        }
    }
    for(int i = 1; i < 13; i++)
    {
        pFloorState->floorShow[i]->setText(QString("%1").arg(i, 2, 10, QChar('0')) + "F: " + QString("%1").arg(pCore->floorClass[i-1]->people.size(), 2, 10, QChar('0')));
    }
}

void StatusDisplayThread::slotAddCount()
{
    double eff;
    totalCount++;
    eff = (double)totalCount / ((double)pCore->steps / 5);
    pStateMonitor->linePeople->setText(QString::number(totalCount));
    pStateMonitor->lineEfficiency->setText(QString::number(eff, 10, 4));
}

void StatusDisplayThread::slotGenerateCount()
{
    generateCount++;
    pStateMonitor->lineWaitingCount->setText(QString::number(generateCount - totalCount));
}
