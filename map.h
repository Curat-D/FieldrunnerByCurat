#ifndef MAP_H
#define MAP_H

#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector>
#include "towerpos.h"
#include "mousehouse.h"
class Map:public QGraphicsItem
{
private:
    int beginX;
    int beginY;
    int endX;
    QList<TowerPos*> positionList;
    static QVector<QPoint*> groundPathList;
    static QVector<QPoint*> aerialPathList;
    MouseHouse* house;
public:
    Map(MouseHouse* HOUSE);
    ~Map();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void loadPos(QPoint* pos1, int len1, QPoint* pos2, int len2);
    void loadPath(QPoint* groundPath, int len1, QPoint* aerialPath, int len2);
    static QPoint advanceGroundPath(int &state,QPoint pos,int speed);
    static QPoint advanceAerialPath(int &state,QPoint pos,int speed);
friend class MainWindow;
};


#endif // MAP_H
