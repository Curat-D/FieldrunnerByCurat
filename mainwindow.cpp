#include <QTime>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "runner.h"
#include "flyer.h"
#include "gattling.h"
#include "towerpos.h"
#include "mousehouse.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , heart(HEART)
{
    ui->setupUi(this);

    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    enemie_timer = new QTimer;
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
    connect(enemie_timer, &QTimer::timeout, this, &MainWindow::addEnemie);
    game_timer->start(100);
    enemie_timer->start(3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addEnemie(){
    Runner* new_runner=new Runner();
    new_runner->setPos(BEGIN_X,BEGIN_Y);
    scene->addItem(new_runner);
    Flyer* new_flyer=new Flyer();
    new_flyer->setPos(BEGIN_X,BEGIN_Y);
    scene->addItem(new_flyer);
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
        enemie_timer->stop();
        music->stop();
        gameOver->play();
    }
}
