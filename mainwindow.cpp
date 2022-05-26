#include <QTime>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "runner.h"
#include "flyer.h"
#include "stubbornrunner.h"
#include "gattling.h"
#include "towerpos.h"
#include "mousehouse.h"
#include "bullet.h"
#include "configreader.h"
int MainWindow::score=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,heart(HEART)
{
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    enemie_timer1 = new QTimer;
    enemie_timer2 = new QTimer;
    enemie_timer3 = new QTimer;
    game_timer = new QTimer;

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle("FieldRunner");

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QPixmap H(":/images/heart.png");
    H = H.scaled(100, 100);
    scene->addPixmap(H)->setPos(1000,50);

    Heart= scene->addText(QString::number(heart));
    QFont font;
    font.setPointSizeF(20);
    font.setBold(true);
    Heart->setFont(font);
    Heart->setPos(1100,90);
    Heart->setDefaultTextColor(Qt::red);

    QPixmap M(":/images/money.png");
    M = M.scaled(100, 100);
    scene->addPixmap(M)->setPos(50,50);

    Money= scene->addText(QString::number(MouseHouse::getCoin()));
    Money->setFont(font);
    Money->setPos(150,90);
    Money->setDefaultTextColor(Qt::yellow);

    Score = scene->addText(QString("Scores: ") +QString::number(score));
    Score->setFont(font);
    Score->setPos(500,90);
    Score->setDefaultTextColor(Qt::blue);

    MouseHouse* house = new MouseHouse();
    house->setPos(400,600);
    scene->addItem(house);

    map= new Map(house);
    map->setPos(0,0);
    scene->addItem(map);

    for(auto pos:map->positionList){
        scene->addItem(pos);
    }

    view = new QGraphicsView(scene, this);
    view->resize(WINDOW_WIDTH+5, WINDOW_HEIGHT+5);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/background.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    music = new QSound(":/musics/game.wav");
    music->setLoops(QSound::Infinite);
    music->play();
    gameOver = new QSound(":/musics/game_over.wav");
    connect(game_timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(game_timer, &QTimer::timeout, this, &MainWindow::checkGameOver);
    connect(enemie_timer1, &QTimer::timeout, this, &MainWindow::addEnemie1);
    connect(enemie_timer2, &QTimer::timeout, this, &MainWindow::addEnemie2);
    connect(enemie_timer3, &QTimer::timeout, this, &MainWindow::addEnemie3);

    game_timer->start(100);
    enemie_timer1->start(2000);
    enemie_timer2->start(3000);
    enemie_timer3->start(4000);

}

MainWindow::~MainWindow()
{
    if(!music)
        delete music;
    if(!gameOver)
        delete gameOver;
}

void MainWindow::addEnemie1(){
    Runner* new_runner=new Runner();
    new_runner->setPos(map->beginX,map->beginY);
    scene->addItem(new_runner);
}

void MainWindow::addEnemie2(){
    Flyer* new_flyer=new Flyer();
    new_flyer->setPos(map->beginX,map->beginY);
    scene->addItem(new_flyer);
}

void MainWindow::addEnemie3(){
    StubbornRunner* new_StubbornRunner=new StubbornRunner();
    new_StubbornRunner->setPos(map->beginX,map->beginY);
    scene->addItem(new_StubbornRunner);
}

void MainWindow::checkGameOver(){
    Money->setPlainText(QString::number(MouseHouse::getCoin()));
    Score->setPlainText(QString("Scores: ") +QString::number(score));

    const QList<QGraphicsItem*> items = scene->items();
    if(!items.isEmpty())
        for(auto item:items)
            if (item!=NULL){
                if(item->x() >= map->endX&&item->type() == Enemie::Type){
                    score-=100;
                    Enemie* enemie = qgraphicsitem_cast<Enemie*>(item);
                    heart-=enemie->getAtk();
                    delete enemie;
                    enemie=NULL;
                    Heart->setPlainText(QString::number(heart));
                    QPixmap H(":/images/heart.png");
                    H = H.scaled(100, 100);
                    scene->addPixmap(H)->setPos(1000,50);
                    QBrush brush(QColor(0, 0, 0, 200));
                    scene->addRect(QRectF(1000,50,100,100-heart),QPen(),brush);
                    scene->advance();
                }
                else if(item->type()==Bullet::Type){
                    Bullet* bullet = qgraphicsitem_cast<Bullet*>(item);
                    if(bullet->getNeedDelete()){
                        delete bullet;
                        bullet=NULL;
                    }
                }
            }

    if(heart<=0){
        scene->addPixmap(QPixmap(":/images/you_lose.jpg").scaled(400,400))->setPos(400, 150);
        scene->advance();
        game_timer->stop();
        enemie_timer1->stop();
        enemie_timer2->stop();
        enemie_timer3->stop();
        music->stop();
        gameOver->play();
        heart=0;
    }
}

void MainWindow::addScore(int increase){
    score+=increase;
}

