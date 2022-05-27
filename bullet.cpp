#include <algorithm>
#include <QDebug>
#include "bullet.h"
#include "tower.h"
#include "enemie.h"
#include "global.h"

Bullet::Bullet(int attack, qreal speedOfX, qreal speedOfY, QString PATH, bool atkOBJECT){
    atk = attack;
    speedX = speedOfX;
    speedY = speedOfY;
    path = PATH;
    atkObject = atkOBJECT;
    needDelete=0;
}

Bullet::~Bullet(){}

QRectF Bullet::boundingRect() const{
    return QRectF(-12, -28, 24, 24);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPixmap p(path);
    p=p.scaled(24,24);
    painter->drawPixmap(QRect(-12, -12, 24, 24), QPixmap(path));
}

bool Bullet::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(!atkObject)
        return other->type() == Tower::Type && (other->y() - y())*(other->y() - y()) + (other->x() - x())*(other->x() - x()) <= ARROW_RADIUS*ARROW_RADIUS;
    else
        return other->type() == Enemie::Type && (other->y() - y())*(other->y() - y()) + (other->x() - x())*(other->x() - x()) <= ARROW_RADIUS*ARROW_RADIUS;
}

int Bullet::type() const{
    return Type;
}

void Bullet::advance(int phase){
    if (!phase)
        return;
    update();
    for(int i=0;i<5;i++){
        QList<QGraphicsItem *> items = collidingItems();
        if (!items.isEmpty()){
            if(!atkObject){
                for(auto item:items){
                    Tower *tower = qgraphicsitem_cast<Tower *>(item);
                    if(tower!=NULL){
                        tower->BeAttacked(atk);
                        if(tower->getHp()<=0){
                            tower->remove();
                            scene()->removeItem(tower);
                        }
                        needDelete=true;
                        return;
                    }
                }
            }
            else{
                for(auto item:items){
                    Enemie *enemie = qgraphicsitem_cast<Enemie *>(item);
                    if(enemie!=NULL){
                        enemie->BeAttacked(atk);
                        if(enemie->getHp()<=0){
                            //delete  enemie;
                            //enemie=NULL;
                            enemie->remove();
                            scene()->removeItem(enemie);
                        }
                        needDelete=true;
                        return;
                    }
                }
            }
        }
        setX(x() + speedX*ARROW_SPEED);
        setY(y() + speedY*ARROW_SPEED);
        update();
    }

    if (x() <=10 || x()>=1100 || y()<=10 || y()>=750){
        needDelete=true;
        return;
    }

}

bool Bullet::getNeedDelete() const{
    return needDelete;
}
