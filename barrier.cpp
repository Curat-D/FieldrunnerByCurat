#include "barrier.h"
#include "enemie.h"
#include "towerGolbal.h"

#include <QDebug>
Barrier::Barrier():Tower(BARRIER_ATK,BARRIER_INTERVAL,BARRIER_RADIUS,BARRIER_HP){
    levelPath=BARRIER1;
    setMovie(levelPath);
}

Barrier::~Barrier(){
    QList<QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty()){
        for(auto item:items){
            Enemie* enemie = qgraphicsitem_cast<Enemie*>(item);
            if(enemie!=NULL){
                enemie->changeActualSpeed(-1); //还原
            }
        }
    }
    return;
}

void Barrier::advance(int phase){
    if(!phase)
        return;
    update();
    if(hp<=0){
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty()){
        for(auto item:items){
            Enemie* enemie = qgraphicsitem_cast<Enemie*>(item);
            if(enemie!=NULL){
                enemie->changeActualSpeed(0);
            }
        }
    }
    update();
    return ;
}
