#include "statemonitor.h"
#pragma execution_character_set("utf-8")

StateMonitor::StateMonitor(QWidget *parent) : QWidget(parent)
{
//Basic Typesetting
    labelRuntime = new QLabel;
    labelPeople = new QLabel;
    labelEfficiency = new QLabel;
    labelEmulation = new QLabel;
    labelWaitingCount = new QLabel;

    lineRunTime = new QLineEdit;
    linePeople = new QLineEdit;
    lineEfficiency = new QLineEdit;
    lineEmulation = new QLineEdit;
    lineWaitingCount = new QLineEdit;

    browserInfoShow = new QTextBrowser;

    buttonSpeedup = new QPushButton;
    buttonSlowdown = new QPushButton;

    VLayout = new QVBoxLayout;
    VLayout_State = new QVBoxLayout;
    HLayoutRuntime = new QHBoxLayout;
    HLayoutPeople = new QHBoxLayout;
    HLayoutEfficiency = new QHBoxLayout;
    HLayoutEmulation = new QHBoxLayout;
    HLayout_Button = new QHBoxLayout;
    HLayoutWaitingCount = new QHBoxLayout;

    this->setLayout(VLayout);

    HLayoutRuntime->addWidget(labelRuntime);
    HLayoutRuntime->addWidget(lineRunTime);
    HLayoutPeople->addWidget(labelPeople);
    HLayoutPeople->addWidget(linePeople);
    HLayoutWaitingCount->addWidget(labelWaitingCount);
    HLayoutWaitingCount->addWidget(lineWaitingCount);
    HLayoutEfficiency->addWidget(labelEfficiency);
    HLayoutEfficiency->addWidget(lineEfficiency);
    HLayoutEmulation->addWidget(labelEmulation);
    HLayoutEmulation->addWidget(lineEmulation);

    HLayout_Button->addWidget(buttonSpeedup);
    HLayout_Button->addWidget(buttonSlowdown);

    VLayout->addLayout(HLayoutRuntime);
    VLayout->addLayout(HLayoutPeople);
    VLayout->addLayout(HLayoutEfficiency);
    VLayout->addLayout(HLayoutEmulation);
    VLayout->addLayout(HLayoutWaitingCount);
    VLayout->addWidget(browserInfoShow);
    VLayout->addLayout(HLayout_Button);

//Detail
    labelRuntime->setText(tr("运行时间："));
    labelPeople->setText(tr("运输人数："));
    labelEfficiency->setText(tr("运输效率："));
    labelEmulation->setText(tr("模拟速度："));
    labelWaitingCount->setText(tr("等待人数："));

    lineRunTime->setMinimumWidth(100);

    lineRunTime->setReadOnly(true);
    lineRunTime->setFrame(0);
    lineRunTime->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(60, 60, 60);");
    linePeople->setReadOnly(true);
    linePeople->setFrame(0);
    linePeople->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(60, 60, 60);");
    lineEfficiency->setReadOnly(true);
    lineEfficiency->setFrame(0);
    lineEfficiency->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(60, 60, 60);");
    lineEmulation->setReadOnly(true);
    lineEmulation->setFrame(0);
    lineEmulation->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(60, 60, 60);");
    lineWaitingCount->setReadOnly(true);
    lineWaitingCount->setFrame(0);
    lineWaitingCount->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(60, 60, 60);");

    labelRuntime->setStyleSheet("color: rgb(231, 231, 231);");
    labelPeople->setStyleSheet("color: rgb(231, 231, 231);");
    labelEfficiency->setStyleSheet("color: rgb(231, 231, 231);");
    labelEmulation->setStyleSheet("color: rgb(231, 231, 231);");
    labelWaitingCount->setStyleSheet("color: rgb(231, 231, 231);");

    browserInfoShow->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(60, 60, 60);border-color: rgb(0, 0, 0);");
    browserInfoShow->setFixedWidth(250);

    buttonSpeedup->setText(tr("加速"));
    buttonSpeedup->setMinimumHeight(40);
    buttonSpeedup->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color: rgb(255, 99, 99);border-radius: 3px;}QPushButton:hover{color: rgb(255, 255, 255);background-color: rgb(255, 88, 88);}QPushButton:pressed{color: rgb(255, 255, 255);background-color: rgb(255, 10, 10);}");

    buttonSlowdown->setText(tr("减速"));
    buttonSlowdown->setMinimumHeight(40);
    buttonSlowdown->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color: rgb(99, 255, 99);border-radius: 3px;}QPushButton:hover{color: rgb(255, 255, 255);background-color: rgb(88, 255, 88);}QPushButton:pressed{color: rgb(255, 255, 255);background-color: rgb(10, 255, 10);}");
}
