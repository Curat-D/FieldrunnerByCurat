#include <QtMath>
#include <QDebug>
#include "glue.h"
#include "towerGolbal.h"
#include "enemie.h"
Glue::Glue():Tower(GLUE_ATK,GLUE_RATE,GLUE_RADIUS,10){
    QString path = QString(GLUE1)+QString("1.png");
    setMovie(path);
    music = new QSound(":/musics/glue.wav");
}

void Glue::advance(int phase){
    if(!phase)
        return;
    QList<QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty()){
        if(music->isFinished())
            music->play();
        Enemie* enemie = qgraphicsitem_cast<Enemie*>(items[0]);
        enemie->BeAttacked(atk*fire_rate);
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
    }
    QString path = QString(GLUE1)+QString::number(direction)+QString(".png");
    setMovie(path);
    update();
}
