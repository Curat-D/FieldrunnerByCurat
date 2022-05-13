#include <QtMath>
#include "gattling.h"
#include "towerGolbal.h"
#include "enemie.h"
Gattling::Gattling():Tower(GATTLING_ATK,GATTLING_INTERVAL,GATTLING_RADIUS,GATTLING_HP){
    QString path = QString(GATTLING1)+QString("1.png");
    setMovie(path);
    music = new QSound(":/musics/gatling.wav");
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
    QString path = QString(GATTLING1)+QString::number(direction)+QString(".png");
    if(count==interval){
        QList<QGraphicsItem *> items = collidingItems();
        if(!items.isEmpty()){
            if(music->isFinished())
                music->play();
            Enemie* enemie = qgraphicsitem_cast<Enemie*>(items[0]);
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
            path = QString(GATTLING1)+QString("shoot/")+QString::number(direction)+QString(".png");
        }
        count=0;
    }
    setMovie(path);
    update();
}
