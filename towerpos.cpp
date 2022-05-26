#include <QGraphicsSceneDragDropEvent>
#include <QtWidgets>
#include <QDebug>

#include "towerpos.h"
#include "global.h"
TowerPos::TowerPos(bool jdg,MouseHouse* HOUSE):hasTower(false),isMelee(jdg),house(HOUSE){
    setAcceptDrops(true);
}

TowerPos::~TowerPos(){
}

QRectF TowerPos::boundingRect() const{
    return QRectF(-POS_SIZE/2,-POS_SIZE/2,POS_SIZE+2,POS_SIZE+2);
}

void TowerPos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(!isMelee)
        painter->drawImage(QRectF(-POS_SIZE/2, -POS_SIZE/2, POS_SIZE, POS_SIZE), QImage(":/images/base.png"));
    else
        painter->drawImage(QRectF(-POS_SIZE/2, -POS_SIZE/2, POS_SIZE, POS_SIZE), QImage(":/images/base1.png"));
}


void TowerPos::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
    if(!hasTower)
        event->setAccepted(event->mimeData()->hasText());
}

// Items can only receive drop events if the last drag move event was accepted.
void TowerPos::dropEvent(QGraphicsSceneDragDropEvent *event){
    if (!hasTower&&event->mimeData()->hasText()) {
        QString s = event->mimeData()->text();

        //近战格子放近战
        if(isMelee){
            if(s!="barrier")
                return;
        }
        else{
            if(s!="gattling1"&&s!="glue1")
                return;
        }
        QPoint pos(x(),y());
        house->addTower(s,pos);
        hasTower=true;
    }
}

int TowerPos::type()const{
    return Type;
}

void TowerPos::removeTower(){
    hasTower=false;
}
