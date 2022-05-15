#include <QtMath>
#include "gattling.h"
#include "towerGolbal.h"
#include "enemie.h"
#include "mousehouse.h"
Gattling::Gattling():Tower(GATTLING_ATK,GATTLING_INTERVAL,GATTLING_RADIUS,GATTLING_HP){
    levelPath = GATTLING1;
    QString path = QString(levelPath)+QString("1.png");
    setMovie(path);
    music = new QSound(":/musics/gatling.wav");
}

Gattling::~Gattling(){
    if(music)
        delete music;
    return;
}

void Gattling::advance(int phase){
    if(!phase)
        return;
    update();
    count++;
    if(hp<=0){
        delete this;
        return;
    }
    QString path = QString(levelPath)+QString::number(direction)+QString(".png");
    if(count==interval){
        QList<QGraphicsItem *> items = collidingItems();
        if(!items.isEmpty()){
            if(music->isFinished())
                music->play();
            Enemie* enemie;
            for(auto item:items){
                enemie = qgraphicsitem_cast<Enemie*>(item);
                if(enemie!=NULL)
                    break;
            }
            if(enemie==NULL)
                return;
            enemie->BeAttacked(atk);

            int x=enemie->x();
            int y=enemie->y();
            if(x==this->x()){
                if(y>this->y())
                    direction=1;
                else
                    direction=19;
            }
            else{
                qreal angel = qAtan((qreal)(y-this->y())/(qreal)(x-this->x()));
                direction = angel*(-18/3.14)+10;
            }
            if(x<this->x())
                direction+=19;
            else
                direction = 20 -direction;
            path = QString(levelPath)+QString("shoot/")+QString::number(direction)+QString(".png");
        }
        count=0;
    }
    setMovie(path);
    update();
}

void Gattling::UpGrade(){
    if(levelPath==GATTLING1){
         levelPath = GATTLING2;
         hp=GATTLING_HP*2;
         atk=GATTLING_ATK*2;
         totalHp=hp;
    }
    else if(levelPath==GATTLING2){
        levelPath = GATTLING3;
        hp=GATTLING_HP*3;
        atk=GATTLING_ATK*2;
        totalHp=hp;
    }
    update();
}
