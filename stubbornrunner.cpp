#include <math.h>
#include <QDebug>
#include "stubbornrunner.h"
#include "tower.h"
#include "map.h"
#include "bullet.h"
#include "enemieGlobal.h"
#include "global.h"

StubbornRunner::StubbornRunner():Enemie(StubbornRunnerHp, StubbornRunnerAtkToTower, StubbornRunnerAtkToHeart,StubbornRunnerSpeed, StubbornRunnerRadius, StubbornRunnerInterval,StubbornRunnerHeight, StubbornRunnerWidth){
    setMoive(StubbornRunnerRight);
}

void StubbornRunner::advance(int phase){
    if (!phase)
        return;
    update();

    count++;
    if(hp<=0){
        delete this;
        return;
    }
    if(count==interval){
        QList<QGraphicsItem *> items = collidingItems();
        if(!items.isEmpty()){
            Tower* tower = qgraphicsitem_cast<Tower*>(items[0]);
            qreal X=tower->x()-x();
            qreal Y=tower->y()-y();
            qreal dis = sqrt(X*X+Y*Y);
            X=X/dis;
            Y=Y/dis;
            Bullet* bullet = new Bullet(atkToTower,X,Y,ARROW_PATH1,ARROW_ATK_TOWER);
            bullet->setPos(x(),y());
            scene()->addItem(bullet);
        }
        count=0;
    }

    QPoint pos(x(),y());
    QPoint new_pos = Map::advanceGroundPath(state,pos,actualSpeed);

    setPos(new_pos);
    if(new_pos.x()>pos.x()){
        if(preState!=enemie_right){
            setMoive(StubbornRunnerRight);
            preState=enemie_right;
        }
    }
    else if(new_pos.x()<pos.x()){
        if(preState!=enemie_left){
            setMoive(StubbornRunnerLeft);
            preState=enemie_left;
        }
    }
    else if(new_pos.y()>pos.y()){
        if(preState!=enemie_down){
            setMoive(StubbornRunnerDown);
            preState=enemie_down;
        }
    }
    else if(new_pos.y()<pos.y()){
        if(preState!=enemie_up){
            setMoive(StubbornRunnerUp);
            preState=enemie_up;
        }
    }
    return;
}

