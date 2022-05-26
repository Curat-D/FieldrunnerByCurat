#include <QPainter>
#include "eliminate.h"
#include "tower.h"
#include "towerGolbal.h"
#include "mousehouse.h"
Eliminate::Eliminate(){
}

QRectF Eliminate::boundingRect()const{
    return QRectF(0,0,ELIMINATE_WIDTH+2,ELIMINATE_HEIGHT+2);
}

void Eliminate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawPixmap(QRect(0, 0, ELIMINATE_WIDTH, ELIMINATE_HEIGHT), QPixmap(ELIMINATE));
}

void Eliminate::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    MouseHouse::addCoin(ELIMINATE_COIN);
    Tower* tower = qgraphicsitem_cast<Tower*>(parentItem());
    if(tower!=NULL)
        delete tower;
    tower=NULL;
    return;
}
