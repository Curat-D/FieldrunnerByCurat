#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

class Tower : public QGraphicsItem
{
public:
    Tower(int ATK=0, int FIRE_RATE=0, int RADIUS=0, int HP=0);
    ~Tower();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    enum { Type = UserType + 2};
    int type() const override;
    void setMovie(QString path);
    void BeAttacked(int damage);
protected:
    int atk;  //攻击力
    int fire_rate;  //攻速
    int radius;     //攻击半径
    int hp;         //生命值
    int direction;   //方向，从1到19
    QMovie* movie;
};

#endif // TOWER_H
