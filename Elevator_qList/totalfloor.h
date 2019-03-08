#ifndef TOTALFLOOR_H
#define TOTALFLOOR_H

#include <QHBoxLayout>
#include "floorinfo.h"

class TotalFloor : public QWidget
{
    Q_OBJECT
public:
    TotalFloor();

    QHBoxLayout* HLayout;

    FloorInfo* floorInfo[3];

private:

};

#endif // TOTALFLOOR_H
