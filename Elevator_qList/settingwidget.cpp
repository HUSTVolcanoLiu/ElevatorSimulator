#include "settingwidget.h"
#pragma execution_character_set("utf-8")

SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(270,120);
    this->setWindowTitle(tr("Settings"));

    layout = new QVBoxLayout;
    layoutCount = new QHBoxLayout;
    layoutDistance = new QHBoxLayout;

    labelCount = new QLabel;
    labelDistance = new QLabel;

    boxCount = new QSpinBox;
    boxDistance = new QSpinBox;

    this->setLayout(layout);
    layoutCount->addWidget(labelCount);
    layoutCount->addWidget(boxCount);
    layout->addLayout(layoutCount);
    layoutDistance->addWidget(labelDistance);
    layoutDistance->addWidget(boxDistance);
    layout->addLayout(layoutDistance);

    labelCount->setText(tr("人数："));
    //labelCount->setFixedWidth(50);
    labelDistance->setText(tr("距离："));
    //labelDistance->setFixedWidth(50);

    boxCount->setRange(0, 100);
    boxCount->setSingleStep(1);
    boxCount->setValue(50);
    boxCount->setSuffix("%");
    boxDistance->setRange(0, 100);
    boxDistance->setSingleStep(1);
    boxDistance->setValue(50);
    boxDistance->setSuffix("%");

    connect(boxCount, SIGNAL(valueChanged(int)), this, SLOT(slotTriggered(int)));
    connect(boxDistance, SIGNAL(valueChanged(int)), this, SLOT(slotTriggered(int)));
}

void SettingWidget::slotTriggered(int i)
{
    if(boxCount->value() != count)
    {
        boxDistance->setValue(100 - boxCount->value());
    }
    else
    {
        boxCount->setValue(100 - boxDistance->value());
    }
    count = boxCount->value();
    distance = boxDistance->value();
    emit signalSendValue(count, distance);
}
