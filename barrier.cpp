#include "barrier.h"
#include "enemie.h"
#include "towerGolbal.h"

#include <QDebug>
Barrier::Barrier():Tower(BARRIER_ATK,BARRIER_INTERVAL,BARRIER_RADIUS,BARRIER_HP){
    setMovie(BARRIER);
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
}

void Barrier::advance(int phase){
    if(!phase)
        return;
    count++;
    if(hp<=0){
        delete this;
        return;
    }
    if(count==interval){
        QList<QGraphicsItem *> items = collidingItems();
        if(!items.isEmpty()){
            Enemie* enemie = qgraphicsitem_cast<Enemie*>(items[0]);
            enemie->BeAttacked(atk);
            for(auto item:items){
                Enemie* enemie = qgraphicsitem_cast<Enemie*>(item);
                if(enemie!=NULL){
                    enemie->changeActualSpeed(0);
                }
            }
        }
        count=0;
    }

    return ;

}
