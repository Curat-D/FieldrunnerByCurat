#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "upgrade.h"
#include "eliminate.h"
class Tower : public QGraphicsItem
{
public:
    Tower(int ATK=0, int INTERVAL=0, int RADIUS=0, int HP=0);
    virtual ~Tower();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    enum { Type = UserType + 2};
    int type() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    int getHp()const;
    void setMovie(QString path);
    void BeAttacked(int damage);
    virtual void UpGrade()=0;
    virtual void remove();
protected:
    int atk;  //攻击力
    int interval;  //攻击间隔
    int count;    //攻击间隔计数
    int radius;     //攻击半径
    int hp;         //生命值
    int totalHp;    //总生命值
    int direction;   //方向，从1到19
    QString levelPath;  //等级对应路径
    QMovie* movie;
private:
    bool ifClicked;  //判断是否被点击
    Upgrade* upgrade; //升级标志
    Eliminate* eliminate; //删除标志
};

#endif // TOWER_H
