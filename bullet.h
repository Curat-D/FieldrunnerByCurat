#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsScene>
#include <QGraphicsItem>
class Bullet : public QGraphicsItem
{
private:
    int atk;
    qreal speedX;
    qreal speedY;
    QString path;
    bool atkObject;   //0:攻击防御塔，1：攻击敌人
public:
    Bullet(int attack = 0, qreal speedOfX = 0, qreal speedOfY = 0, QString PATH=0, bool atkOBJECT=0);
    ~Bullet();
    enum { Type = UserType + 3 };
    int type() const override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *Object, Qt::ItemSelectionMode mode) const override;

    void advance(int phase) override;
};


#endif // BULLET_H
