#include <QPainter>
#include <QDebug>
#include "upgrade.h"
#include "towerGolbal.h"
#include "tower.h"
#include "mousehouse.h"
Upgrade::Upgrade(){
}

QRectF Upgrade::boundingRect()const{
    return QRectF(0,0,UPGRADE_WIDTH+2,UPGRADE_HEIGHT+2);
}

void Upgrade::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawPixmap(QRect(0, 0, UPGRADE_WIDTH, UPGRADE_HEIGHT), QPixmap(UPGRADE));
}

void Upgrade::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    int coin=MouseHouse::getCoin();
    if(coin<UPGRADE_COIN)
        return;
    MouseHouse::addCoin(-UPGRADE_COIN);
    Tower* tower = qgraphicsitem_cast<Tower*>(parentItem());
    tower->UpGrade();
    return;
}
