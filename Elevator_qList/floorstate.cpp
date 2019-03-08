#include "floorstate.h"
#pragma execution_character_set("utf-8")

FloorState::FloorState(QWidget *parent) : QWidget(parent)
{
    VLayout = new QVBoxLayout;
    settingWidget = new SettingWidget;
    this->setLayout(VLayout);

    for(int i = 12; i >= 0; i--)
    {
        floorShow[i] = new QPushButton;
        VLayout->addWidget(floorShow[i]);

        floorShow[i]->setText(QString::number(i));
        floorShow[i]->setFixedWidth(70);
        floorShow[i]->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        floorShow[i]->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color: rgb(127, 127, 127);border-radius: 0px;}QPushButton:hover{color: rgb(255, 255, 255);background-color: rgb(95, 95, 95);}QPushButton:pressed{color: rgb(255, 255, 255);background-color: rgb(63, 63, 63);}");
    }
    floorShow[0]->setText(tr("设置"));
    VLayout->setSpacing(0);
    VLayout->setMargin(0);

    QObject::connect(this->floorShow[0],&QPushButton::clicked,this->settingWidget,&QWidget::show);
}
