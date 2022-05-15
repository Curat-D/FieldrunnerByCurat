#ifndef CARD_H
#define CARD_H
#include <QGraphicsItem>
#include <QPainter>
#include <QtWidgets>

class MouseHouse;
class Card : public QGraphicsItem
{
public:
    Card(int idx);
    ~Card(){};
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
private:
    int index;   //index in the vector
    int count;   //count of cool
    //all cards share a Vector(get value by index)
    const static QVector<QString> name;
    const static QVector<int> cost;
    const static QVector<int> cool;

    friend class MouseHouse;
};

#endif // CARD_H
