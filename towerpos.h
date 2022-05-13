#ifndef TOWERPOS_H
#define TOWERPOS_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
class TowerPos : public QGraphicsItem{
public:
    TowerPos(bool jdg);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    enum{Type = UserType+4};
    int type() const override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    void removeTower();

private:
    bool hasTower;
    const bool isMelee;  //1:近战格子， 0：远程格子
};

#endif // TOWERPOS_H
