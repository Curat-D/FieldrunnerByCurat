#include "enemie.h"
#include "tower.h"
#include "towerpos.h"
#include "enemieGlobal.h"
#include "global.h"
#include <QDebug>
Enemie::Enemie(int HP,int ATK1, int ATK2, int SPEED, int Radius, int INTERVAL,int Height, int Weight){
    hp=HP;
    atkToTower=ATK1;
    atkToHeart=ATK2;
    speed=SPEED;
    radius=Radius;
    actualSpeed=speed;
    interval=INTERVAL;
    count=0;
    H=Height;
    W=Weight;
    movie=NULL;
    state = 1;
    preState = enemie_right;
}

Enemie::~Enemie(){
    if(movie)
        delete movie;

}

QRectF Enemie::boundingRect() const{
    return QRectF(-W/2,-H/2,W+2,H+2);
}

void Enemie::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QImage image = movie->currentImage();
 //   qDebug()<<"敌人："<<x()<<" "<<y();
    painter->drawImage(QRectF(-W/2,-H/2,W,H), image);
}

bool Enemie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const{
    Q_UNUSED(mode);
    return other->type()==Tower::Type && (other->y() - y())*(other->y() - y()) + (other->x() - x())*(other->x() - x()) <= radius*radius;

}

int Enemie::type() const{
    return Type;
}


void Enemie::BeAttacked(int damage){
    hp-=damage;
}

void Enemie::setMoive(QString path){
    if(movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}

int Enemie::getAtk()const{
    return atkToHeart;
}

void Enemie::changeActualSpeed(int Speed){
    if(Speed==-1)
        actualSpeed=speed;
    else
        actualSpeed=Speed;
}

