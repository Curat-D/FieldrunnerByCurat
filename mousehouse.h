#ifndef MOUSEHOUSE_H
#define MOUSEHOUSE_H

#include <QGraphicsItem>
#include "card.h"

class MouseHouse : public QGraphicsItem
{
public:
    MouseHouse();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  //  void addTower(QString s, QPointF pos);
private:
    QVector<Card*> card_vec;  //vector of cards
};

#endif // MOUSEHOUSE_H
