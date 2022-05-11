#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsScene>
#include <QGraphicsItem>

class Bullet : public QGraphicsItem
{
public:
    Bullet(int ATK=0, qreal SPEED=0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *Object, Qt::ItemSelectionMode mode) const override;

    void advance(int phase) override;

private:
    int atk;
    qreal speed;

};

#endif // BULLET_H
