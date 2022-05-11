#ifndef MAP_H
#define MAP_H

#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector>
#include "towerpos.h"

class Map:public QGraphicsItem
{
private:
    QList<TowerPos*> positionList;
    static QVector<QPoint*> groundPathList;
    static QVector<QPoint*> aerialPathList;
public:
    Map();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void loadPos();
    void loadPath();
    static QPoint advanceGroundPath(int &state,QPoint pos,int speed);
    static QPoint advanceAerialPath(int &state,QPoint pos,int speed);
friend class MainWindow;
};


#endif // MAP_H
