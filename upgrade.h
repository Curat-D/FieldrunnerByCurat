#ifndef UPGRADE_H
#define UPGRADE_H
#include <QGraphicsItem>

class Upgrade: public QGraphicsItem
{
public:
    Upgrade();
    ~Upgrade(){};
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // UPGRADE_H
