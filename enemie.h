#ifndef ENEMIE_H
#define ENEMIE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QMovie>

enum EnemieState{enemie_left,enemie_right,enemie_up,enemie_down};
//abstract class of Enemie
class Enemie : public QGraphicsItem{
public:
    Enemie(int HP=0,int ATK1=0, int ATK2=0, int SPEED=0, int radius=0, int INTERVAL=0,int Height=0, int Weight=0);
    virtual ~Enemie();

    QRectF boundingRect() const override;
    //draw
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    //type
    enum { Type = UserType + 1 };
    int type() const override;

    void BeAttacked(int damage);
    void setMoive(QString path);
    int getAtk()const;
    void changeActualSpeed(int speed);
protected:
    int hp;
    int totalHp;  //总血量（用于计算百分比显示血条）
    int atkToTower;
    int atkToHeart;
    int speed;
    int state;
    int radius;
    int actualSpeed;  //可能被阻拦、减速
    int interval;   //攻击间隔
    int count;     //攻击间隔计数
    EnemieState preState;  //用来判断是否需要改变动画（方向是否改变）
private:
    QMovie* movie;
    int H;
    int W;
};

#endif // ENEMIE_H
