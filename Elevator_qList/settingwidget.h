#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);

    QVBoxLayout* layout;
    QHBoxLayout* layoutCount;
    QHBoxLayout* layoutDistance;

    QLabel* labelCount;
    QLabel* labelDistance;

    QSpinBox* boxCount;
    QSpinBox* boxDistance;

    int count = 50;
    int distance = 50;

signals:
    void signalSendValue(int, int);

public slots:
    void slotTriggered(int i);

private:

};

#endif // SETTINGWIDGET_H
