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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , heart(HEART)
{
    ui->setupUi(this);

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

    map= new Map();
    map->setPos(0,0);
    scene->addItem(map);

    for(auto pos:map->positionList){
        scene->addItem(pos);
    }

    MouseHouse* house = new MouseHouse();
    house->setPos(780,660);
    scene->addItem(house);

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
    delete ui;
}

void MainWindow::addEnemie1(){
    Runner* new_runner=new Runner();
    new_runner->setPos(BEGIN_X,BEGIN_Y);
    scene->addItem(new_runner);
}

void MainWindow::addEnemie2(){
    Flyer* new_flyer=new Flyer();
    new_flyer->setPos(BEGIN_X,BEGIN_Y);
    scene->addItem(new_flyer);
}

void MainWindow::addEnemie3(){
    StubbornRunner* new_StubbornRunner=new StubbornRunner();
    new_StubbornRunner->setPos(BEGIN_X+100,BEGIN_Y);
    scene->addItem(new_StubbornRunner);
}

void MainWindow::checkGameOver(){
    const QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem * item, items)
        if (item->type() == Enemie::Type && item->x() >= END_X){
            Enemie* enemie = qgraphicsitem_cast<Enemie*>(item);
            heart-=enemie->getAtk();
            delete enemie;
            QPixmap H(":/images/heart.png");
            H = H.scaled(100, 100);
            scene->addPixmap(H)->setPos(1000,50);
            QBrush brush(QColor(0, 0, 0, 200));
            scene->addRect(QRectF(1000,50,100,100-heart),QPen(),brush);
            scene->advance();
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
    }
}

void MainWindow::advanceBulllet(){
    const QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem * item, items)
        if(item->type()==Bullet::Type){
            item->advance(0);
            item->advance(1);
        }
}
