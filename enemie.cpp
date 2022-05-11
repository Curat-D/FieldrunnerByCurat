#include "enemie.h"
#include "enemieGlobal.h"
#include "global.h"
#include <QDebug>
Enemie::Enemie(int HP,int ATK, int SPEED, int Height, int Weight){
    hp=HP;
    atk=ATK;
    speed=SPEED;
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
    return atk;
}


