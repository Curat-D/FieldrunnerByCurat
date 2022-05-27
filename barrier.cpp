#include "barrier.h"
#include "enemie.h"
#include "towerGolbal.h"

#include <QDebug>
Barrier::Barrier():Tower(BARRIER_ATK,BARRIER_INTERVAL,BARRIER_RADIUS,BARRIER_HP){
    levelPath=BARRIER1;
    setMovie(levelPath);
}

Barrier::~Barrier(){
}

void Barrier::remove(){
    QList<QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty()){
        for(auto item:items){
            Enemie* enemie = qgraphicsitem_cast<Enemie*>(item);
            if(enemie!=NULL){
                enemie->changeActualSpeed(-1); //还原
            }
        }
    }
}

void Barrier::advance(int phase){
    if(!phase)
        return;
    update();
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
