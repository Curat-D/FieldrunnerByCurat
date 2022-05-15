#include "mousehouse.h"
#include "gattling.h"
#include "glue.h"
#include "barrier.h"
#include "global.h"
int MouseHouse::coins=300;
MouseHouse::MouseHouse(){
    Card* card;
    for (int i = 0; i < CARD_NUM; i++){
        card = new Card(i);
        card->setParentItem(this);
        card->setPos(MOUSEHOSE_WIDTH * i+10, 5);
        card_vec.push_back(card);
    }
}

MouseHouse::~MouseHouse(){
    qDeleteAll(card_vec);
    return;
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

void MouseHouse::advance(int phase){
    if (!phase)
        return;
    update();
}

void MouseHouse::addTower(QString s, QPointF pos){
   // qDebug()<<pos;
    int idx=Card::name.indexOf(s);
    coins-=Card::cost[idx];
    Tower* tower=NULL;
    switch (idx) {
    case 0:
        tower=new Gattling();
        tower->setPos(pos);
        scene()->addItem(tower);
        break;
    case 1:
        tower=new Glue();
        tower->setPos(pos);
        scene()->addItem(tower);
        break;
    case 2:
        tower=new Barrier();
        tower->setPos(pos);
        scene()->addItem(tower);
        break;
    }
    card_vec[idx]->count = 0;
}

int MouseHouse::getCoin(){
    return coins;
}

void MouseHouse::addCoin(int increase){
    coins+=increase;
}
