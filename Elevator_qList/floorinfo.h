#ifndef FLOORINFO_H
#define FLOORINFO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class FloorInfo : public QWidget
{
    Q_OBJECT
public:
    explicit FloorInfo(QWidget *parent = nullptr);

    QLabel* floor[12];
    QPushButton* controlElevator;
    QVBoxLayout* VLayout;

    QString styleOrigin, styleOrigin2, styleRunning, stylePause, styleStop;

signals:

public slots:

private:
};

#endif // FLOORINFO_H
