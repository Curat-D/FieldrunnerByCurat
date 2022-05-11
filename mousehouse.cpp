#include "mousehouse.h"
#include "global.h"
MouseHouse::MouseHouse(){
    Card* card;
    for (int i = 0; i < CARD_NUM; i++){
        card = new Card(i);
        card->setParentItem(this);
        card->setPos(CARD_WIDTH * i, 5);
        card_vec.push_back(card);
    }
}

QRectF MouseHouse::boundingRect() const{
    return QRectF(0, 0, MOUSEHOSE_WIDTH*CARD_NUM, MOUSEHOSE_HEIGHT);
}

void MouseHouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    for (int i = 0; i < CARD_NUM; i++){
        painter->drawPixmap(QRect(MOUSEHOSE_WIDTH*i, 0, MOUSEHOSE_WIDTH, MOUSEHOSE_HEIGHT), QPixmap(":/images/mousehouse.png"));
    }
}
