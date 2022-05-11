#ifndef ENEMIE_H
#define ENEMIE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QMovie>

enum EnemieState{enemie_left,enemie_right,enemie_up,enemie_down};
//abstract class of Enemie
class Enemie : public QGraphicsItem
{
public:
    Enemie(int HP=0,int ATK=0, int SPEED=0, int Height=0, int Weight=0);
    ~Enemie();

    QRectF boundingRect() const override;
    //draw
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    //type
    enum { Type = UserType + 1 };
    int type() const override;

    void BeAttacked(int damage);
    void setMoive(QString path);
    int getAtk()const;
protected:
    int hp;
    int atk;
    int speed;
    int state;
    EnemieState preState;
private:
    QMovie* movie;
    int H;
    int W;
};

#endif // ENEMIE_H
