#include <math.h>
#include "map.h"
#include "global.h"
QVector<QPoint*> Map::groundPathList=QVector<QPoint*>();
QVector<QPoint*> Map::aerialPathList=QVector<QPoint*>();

Map::Map(){
    loadPos();
    loadPath();
}

QRectF Map::boundingRect() const{
    return QRectF(0, 0, MAP_WIDTH, MAP_HEIGHT);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


void Map::loadPos(){
    QPoint pos1[] ={
        QPoint(270, 270),
        QPoint(270, 180),
        QPoint(360, 460),
        QPoint(600, 180),

        QPoint(930, 270),
        QPoint(930, 180),
        QPoint(840, 450),
        QPoint(930, 510),

    };//远程
    int len	= sizeof(pos1) / sizeof(pos1[0]);

    for (int i = 0; i < len; ++i){
        TowerPos* newPos=new TowerPos(false);
        newPos->setPos(pos1[i]);
        positionList.push_back(newPos);
    }
    QPoint pos2[] ={
        QPoint(100, 410),
        QPoint(200, 410),
        QPoint(400, 250),
        QPoint(490, 450),
        QPoint(600, 350),
        QPoint(710, 450),

    };//远程
    len	= sizeof(pos2) / sizeof(pos2[0]);

    for (int i = 0; i < len; ++i){
        TowerPos* newPos=new TowerPos(true);
        newPos->setPos(pos2[i]);
        positionList.push_back(newPos);
    }
}

void Map::loadPath(){
    QPoint groundPath[]{
        QPoint(0, 410),
        QPoint(230, 410),
        QPoint(330, 350),
        QPoint(330, 250),
        QPoint(540, 250),
        QPoint(540, 450),
        QPoint(440, 450),
        QPoint(440, 350),

        QPoint(760, 350),
        QPoint(760, 450),
        QPoint(660, 450),
        QPoint(660, 250),
        QPoint(870, 250),
        QPoint(870, 350),
        QPoint(970, 410),
        QPoint(1020, 410),
    };
    int len	= sizeof(groundPath) / sizeof(groundPath[0]);

    for (int i = 0; i < len; ++i){
        QPoint* new_point=new QPoint(groundPath[i]);
        groundPathList.push_back(new_point);
    }

    QPoint aerialPath[]{
        QPoint(0, 410),
        QPoint(1020, 410),
    };
    len	= sizeof(aerialPath) / sizeof(aerialPath[0]);

    for (int i = 0; i < len; ++i){
        QPoint* new_point=new QPoint(aerialPath[i]);
        aerialPathList.push_back(new_point);
    }
}

QPoint Map::advanceGroundPath(int& state,QPoint pos,int speed){
    if(state==groundPathList.size())
        return *groundPathList[state-1];
    QPoint** data=groundPathList.data();
    QPoint p1=*data[state-1];
    QPoint p2=*data[state];
    double dis = sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()));
    int X = pos.x();
    int Y = pos.y();
    double x_dis = (double)speed*(p2.x()-p1.x())/dis;
    double y_dis = (double)speed*(p2.y()-p1.y())/dis;
    X+=x_dis;
    Y+=y_dis;
    if(X<qMin(p1.x(),p2.x())
        ||X>qMax(p1.x(),p2.x())
        ||Y<qMin(p1.y(),p2.y())
        ||Y>qMax(p1.y(),p2.y())
        ||(X==p1.x()&&Y==p1.y())
        ||(X==p2.x()&&Y==p2.y())){
        state+=1;
        X=p2.x();
        Y=p2.y();
    }
    return QPoint(X,Y);
}

QPoint Map::advanceAerialPath(int& state,QPoint pos,int speed){
    if(state==aerialPathList.size())
        return *aerialPathList[state-1];
    QPoint** data=aerialPathList.data();
    QPoint p1=*data[state-1];
    QPoint p2=*data[state];
    double dis = sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()));
    int X = pos.x();
    int Y = pos.y();
    double x_dis = (double)speed*(p2.x()-p1.x())/dis;
    double y_dis = (double)speed*(p2.y()-p1.y())/dis;
    X+=x_dis;
    Y+=y_dis;
    if(X<qMin(p1.x(),p2.x())
        ||X>qMax(p1.x(),p2.x())
        ||Y<qMin(p1.y(),p2.y())
        ||Y>qMax(p1.y(),p2.y())
        ||(X==p1.x()&&Y==p1.y())
        ||(X==p2.x()&&Y==p2.y())){
        state+=1;
        X=p2.x();
        Y=p2.y();
    }
    return QPoint(X,Y);
}
