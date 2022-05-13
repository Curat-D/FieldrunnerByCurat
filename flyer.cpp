#include "flyer.h"
#include "map.h"
#include "enemieGlobal.h"
#include "global.h"

Flyer::Flyer():Enemie(FlyerHp, FlyerAtkToTower, FlyerAtkToHeart, FlyerSpeed, FlyerInterval,FlyerRadius,FlyerHeight, FlyerWidth){
    setMoive(FlyerMoive);
}

void Flyer::advance(int phase){
    if (!phase)
        return;
    update();

    if(hp<=0){
        delete this;
        return;
    }

    QPoint pos(x(),y());
    QPoint new_pos = Map::advanceAerialPath(state,pos,speed);
    setPos(new_pos);
    return;
}

