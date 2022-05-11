#include <QGraphicsSceneDragDropEvent>
#include <QtWidgets>

#include <QDebug>
#include "gattling.h"
#include "glue.h"
#include "towerpos.h"
#include "global.h"
TowerPos::TowerPos(bool jdg):hasTower(false),isMelee(jdg){
    setAcceptDrops(true);
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
        QPointF pos(x(),y());
       // qDebug()<<pos;
        if(s=="gattling1"){
            Gattling* g=new Gattling();
            g->setPos(pos);
            scene()->addItem(g);
        }
        else if(s=="glue1"){
            Glue* g=new Glue();
            g->setPos(pos);
            scene()->addItem(g);
        }
        hasTower=true;
    }
}
