#include "totalfloor.h"

TotalFloor::TotalFloor()
{
    HLayout = new QHBoxLayout;
    this->setLayout(HLayout);
    for(int i = 0; i <= 2; i++)
    {
        floorInfo[i] = new FloorInfo;
        HLayout->addWidget(floorInfo[i]);
    }
    HLayout->setSpacing(5);
    HLayout->setMargin(0);
}
