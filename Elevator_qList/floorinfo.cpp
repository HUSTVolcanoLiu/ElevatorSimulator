#include "floorinfo.h"

FloorInfo::FloorInfo(QWidget *parent) : QWidget(parent)
{
    VLayout = new QVBoxLayout;

    styleOrigin = "color: rgb(255, 255, 255); background-color: rgb(50, 50, 50); font-size:30px;";
    styleOrigin2 = "color: rgb(255, 255, 255); background-color: rgb(30, 30, 30); font-size:30px;";
    styleRunning = "color: rgb(255, 255, 255); background-color: rgb(50, 200, 50);";
    stylePause = "color: rgb(255, 255, 255); background-color: rgb(210, 100, 0);";
    styleStop = "color: rgb(255, 255, 255); background-color: rgb(200, 0, 0);";

    for(int i = 11; i >= 0; i--)
    {
        floor[i] = new QLabel;
        VLayout->addWidget(floor[i]);
        floor[i]->setText(tr("Label"));
        floor[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        floor[i]->setAlignment(Qt::AlignCenter);
        i % 2 ? floor[i]->setStyleSheet(styleOrigin) : floor[i]->setStyleSheet(styleOrigin2);
    }
    controlElevator = new QPushButton;
    controlElevator->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color: rgb(111, 111, 111);;border-radius: 0px;}QPushButton:hover{color: rgb(255, 255, 255);background-color: rgb(95, 95, 95);}QPushButton:pressed{color: rgb(255, 255, 255);background-color: rgb(63, 63, 63);}");
    controlElevator->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    VLayout->addWidget(controlElevator);
    VLayout->setSpacing(0);
    VLayout->setMargin(0);

    this->setLayout(VLayout);
}
