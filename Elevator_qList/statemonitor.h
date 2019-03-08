#ifndef STATEMONITOR_H
#define STATEMONITOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QLabel>

class StateMonitor : public QWidget
{
    Q_OBJECT
public:
    explicit StateMonitor(QWidget *parent = nullptr);
    QLabel* labelRuntime;
    QLabel* labelPeople;
    QLabel* labelEfficiency;
    QLabel* labelEmulation;
    QLabel* labelWaitingCount;

    QLineEdit* lineRunTime;
    QLineEdit* linePeople;
    QLineEdit* lineEfficiency;
    QLineEdit* lineEmulation;
    QLineEdit* lineWaitingCount;

    QTextBrowser* browserInfoShow;

    QPushButton* buttonSpeedup;
    QPushButton* buttonSlowdown;

    QVBoxLayout* VLayout;
    QHBoxLayout* HLayoutRuntime;
    QHBoxLayout* HLayoutPeople;
    QHBoxLayout* HLayoutEfficiency;
    QHBoxLayout* HLayoutEmulation;
    QHBoxLayout* HLayoutWaitingCount;
    QVBoxLayout* VLayout_State;
    QHBoxLayout* HLayout_Button;

signals:

public slots:

private:

};

#endif // STATEMONITOR_H
