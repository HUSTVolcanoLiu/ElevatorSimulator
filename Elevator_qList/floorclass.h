#ifndef FLOORCLASS_H
#define FLOORCLASS_H

#include <QObject>

class FloorClass : public QObject
{
    Q_OBJECT
public:
    explicit FloorClass(QObject *parent = nullptr);

    //成员队列
    QList<int> people;

signals:

public slots:
};

#endif // FLOORCLASS_H
