#include <math.h>
#include "configreader.h"
#include "map.h"
#include "global.h"
QVector<QPoint*> Map::groundPathList=QVector<QPoint*>();
QVector<QPoint*> Map::aerialPathList=QVector<QPoint*>();

Map::Map(MouseHouse* HOUSE):house(HOUSE){
    QPoint* pos1=NULL,*pos2=NULL,*groundPath=NULL,*aerialPath=NULL;
    int len1=0,len2=0,len3,len4;
    ConfigReader::readConfig(pos1,len1,pos2,len2,groundPath,len3,aerialPath,len4,beginX,beginY,endX);
    loadPos(pos1,len1,pos2,len2);
    loadPath(groundPath,len3,aerialPath,len4);
    delete pos1;
    delete pos2;
    delete groundPath;
    delete aerialPath;
    pos1=NULL;
    pos2=NULL;
    groundPath=NULL;
    aerialPath=NULL;
}

Map::~Map(){
    //qDeleteAll(positionList);
}

QRectF Map::boundingRect() const{
    return QRectF(0, 0, MAP_WIDTH, MAP_HEIGHT);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


void Map::loadPos(QPoint* pos1, int len1, QPoint* pos2, int len2){
    for (int i = 0; i < len1; ++i){
        TowerPos* newPos=new TowerPos(false,house);
        newPos->setPos(pos1[i]);
        positionList.push_back(newPos);
    }
    for (int i = 0; i < len2; ++i){
        TowerPos* newPos=new TowerPos(true,house);
        newPos->setPos(pos2[i]);
        positionList.push_back(newPos);
    }
}

void Map::loadPath(QPoint* groundPath, int len1, QPoint* aerialPath, int len2){
    for (int i = 0; i < len1; ++i){
        QPoint* new_point=new QPoint(groundPath[i]);
        groundPathList.push_back(new_point);
    }
    for (int i = 0; i < len2; ++i){
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
