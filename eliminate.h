#ifndef ELIMINATE_H
#define ELIMINATE_H
#include <QGraphicsItem>

class Eliminate : public QGraphicsItem
{
public:
    Eliminate();
    ~Eliminate(){};
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // ELIMINATE_H
