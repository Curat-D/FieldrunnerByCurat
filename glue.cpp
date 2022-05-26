#include <QtMath>
#include <QDebug>
#include "glue.h"
#include "bullet.h"
#include "enemie.h"
#include "map.h"
#include "global.h"
#include "towerGolbal.h"

Glue::Glue():Tower(GLUE_ATK,GLUE_INTERVAL,GLUE_RADIUS,GLUE_HP){
    levelPath=GLUE1;
    QString path = QString(levelPath)+QString("1.png");
    setMovie(path);
    music = new QSound(":/musics/glue.wav");
}

Glue::~Glue(){
    if(music)
        delete music;
     music = NULL;
    return;
}

void Glue::advance(int phase){
    if(!phase)
        return;
    update();
    count++;
    if(count==interval){
        QList<QGraphicsItem *> items = collidingItems();
        if(!items.isEmpty()){
            if(music->isFinished())
                music->play();
            Enemie* enemie=NULL;
            for(auto item:items){
                enemie = qgraphicsitem_cast<Enemie*>(item);
                if(enemie!=NULL)
                    break;
            }
            if(enemie==NULL)
                return;
            qreal X=enemie->x()-x();
            qreal Y=enemie->y()-y();
            qreal dis = sqrt(X*X+Y*Y);
            X=X/dis;
            Y=Y/dis;
            Bullet* bullet = new Bullet(atk,X,Y,ARROW_PATH2,ARROW_ATK_ENEMIE);
            bullet->setPos(x(),y());
            scene()->addItem(bullet);

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
        count=0;
    }

    QString path = QString(levelPath)+QString::number(direction)+QString(".png");
    setMovie(path);
    update();
}

void Glue::UpGrade(){
    if(levelPath==GLUE1){
         levelPath = GLUE2;
         hp=GLUE_HP*2;
         atk=GLUE_ATK*2;
         totalHp=hp;
    }
    else if(levelPath==GLUE2){
        levelPath = GLUE3;
        hp=GLUE_HP*3;
        atk=GLUE_ATK*2;
        totalHp=hp;
    }
    update();
}
