#include "card.h"
#include "global.h"

const QVector<QString> Card::name = {"gattling1","glue1","car"};
Card::Card(int idx):index(idx){}
QRectF Card::boundingRect() const{
    return QRectF(0, 0, CARD_WIDTH+2, CARD_HEIGHT+2);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)


    //painter->drawPixmap(QRect(-CARD_WIDTH/2, -CARD_HEIGHT/2, CARD_WIDTH+2, CARD_HEIGHT+2), QPixmap(":/images/Towers/" + name[index] + ".png"));
    painter->drawPixmap(QRect(0, 0, CARD_WIDTH+2, CARD_HEIGHT+2), QPixmap(":/images/Towers/" + name[index] + ".png"));

}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    event->setAccepted(true);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // start a drag and drop operation after the user has moved the cursor a certain distance with a button held down,
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(event->widget()); //event->widget事件所属的窗口
    QMimeData *md = new QMimeData; //QMimeData类为数据提供一个容器,用来记录关于MIME类型数据的信息 QMimeData常用来描述保存在剪切板或者拖拽里的信息
    md->setText(name[index]);
    drag->setMimeData(md);

    QPixmap pixMap(":/images/Towers/"  + name[index] + ".png");
    drag->setPixmap(pixMap);
    drag->setHotSpot(QPoint(CARD_WIDTH/2, CARD_HEIGHT/2));
    drag->exec();
}
