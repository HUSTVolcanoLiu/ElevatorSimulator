#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QWidget>
#include <QHBoxLayout>
#include<QThread>
#include "statemonitor.h"
#include "floorstate.h"
#include "totalfloor.h"
#include "core.h"

static int totalCount = 0;
static int generateCount = 0;

class ElevatorDisplayThread : public QThread
{
    Q_OBJECT
public:
    explicit ElevatorDisplayThread(QObject *parent = nullptr);
    void UIsetElevatorPointer(TotalFloor* totFl);
    void setElevatorPointer(ElevatorClass* elev);
    void setFloorPointer(FloorClass* floo[12]);
    QString styleOrigin, styleRunning, stylePause, styleStop;

    TotalFloor* pTotalFloor;
    ElevatorClass* pElevatorClass;
    FloorClass* pFloorClass[12];

    int num;

signals:

public slots:
    void slotFlushInfo();

};

class StatusDisplayThread : public QThread
{
    Q_OBJECT
public:
    explicit StatusDisplayThread(QObject *parent = nullptr);
    void UIsetElevatorPointer(TotalFloor* totFl);
    void setElevatorPointer(ElevatorClass* elev[3]);
    void setStateMoniterPointer(StateMonitor* statM);
    void setCorePointer(Core* co);
    void setFloorStatePointer(FloorState* flo);
    QString styleOrigin, styleRunning, stylePause;

    TotalFloor* pTotalFloor;
    ElevatorClass* pElevatorClass[3];
    StateMonitor* pStateMonitor;
    Core* pCore;
    FloorState* pFloorState;

    double effi;

signals:

public slots:
    void slotFlushInfo();
    void slotAddCount();
    void slotGenerateCount();

};

class Elevator : public QWidget
{
    Q_OBJECT

public:
    Elevator(QWidget *parent = 0);
    ~Elevator();

public slots:
    void slotShowSpeed();

private:
    Core* core;

    QHBoxLayout* HLayout;

    StateMonitor* stateMonitor;

    FloorState* floorState;

    TotalFloor* totalFloor;

    ElevatorDisplayThread* elevatorDisplayThread[3];
    StatusDisplayThread* statusDisplayThread;
};

#endif // ELEVATOR_H
