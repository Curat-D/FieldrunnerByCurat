#include "tower.h"
#include "enemie.h"
#include "towerGolbal.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
Tower::Tower(int ATK, int FIRE_RATE, int RADIUS, int HP){
    atk=ATK;
    fire_rate=FIRE_RATE;
    radius=RADIUS;
    hp=HP;
    direction=1;
    movie=NULL;
}

Tower::~Tower(){
    delete movie;
    movie=NULL;
}

QRectF Tower::boundingRect() const {
     return QRectF(-qMax(TOWER_WIDTH/2,radius),-qMax(TOWER_HEIGHT/2,radius),qMax(TOWER_WIDTH,2*radius)+2,qMax(TOWER_HEIGHT,2*radius)+2);
 //   return QRectF(-TOWER_WIDTH/2,-TOWER_HEIGHT/2,2*radius+2,2*radius+2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawImage(QRectF(-radius,-radius, 2*radius, 2*radius), QImage(RANGE));
  //  painter->drawEllipse(QRectF(-radius/2,-radius/2,radius, radius));
   // painter->drawRect(QRectF(-TOWER_WIDTH/2,-TOWER_HEIGHT/2,TOWER_WIDTH+2,TOWER_HEIGHT+2));
    QImage image = movie->currentImage();
    painter->drawImage(QRectF(-TOWER_WIDTH/2, -TOWER_HEIGHT/2, TOWER_WIDTH, TOWER_HEIGHT), image);

}

bool Tower::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const{
    Q_UNUSED(mode);
/*    if(other->type()==Enemie::Type){
        qDebug()<<"塔："<<other->x()<<" "<<other->y()<<" "<<x()<<" "<<y();
        qDebug()<<"距离 "<<(other->y() - y())*(other->y() - y()) + (other->x() - x())*(other->x() - x());
    }*/

    return other->type()==Enemie::Type && (other->y() - y())*(other->y() - y()) + (other->x() - x())*(other->x() - x()) <= radius*radius;
}

int Tower::type() const{
    return Type;
}


void Tower::setMovie(QString path){
    if(movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}

void Tower::BeAttacked(int damage){
    hp-=damage;
}
