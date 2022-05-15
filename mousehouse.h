#ifndef MOUSEHOUSE_H
#define MOUSEHOUSE_H

#include <QGraphicsItem>
#include "card.h"

class MouseHouse : public QGraphicsItem
{
public:
    MouseHouse();
    ~MouseHouse();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void addTower(QString s, QPointF pos);
    static int getCoin();
    static void addCoin(int increase);
private:
    QVector<Card*> card_vec;  //vector of cards
    static int coins;
};

#endif // MOUSEHOUSE_H
