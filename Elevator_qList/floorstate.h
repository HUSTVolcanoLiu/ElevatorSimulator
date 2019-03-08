#ifndef FLOORSTATE_H
#define FLOORSTATE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "settingwidget.h"

class FloorState : public QWidget
{
    Q_OBJECT
public:
    explicit FloorState(QWidget *parent = nullptr);

    QPushButton* floorShow[13];

    QVBoxLayout* VLayout;

    SettingWidget* settingWidget;

signals:

public slots:

private:
};

#endif // ELEVATORCONTROL_H
