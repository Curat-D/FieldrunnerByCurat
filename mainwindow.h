#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QSound>
#include "map.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addEnemie1();
    void addEnemie2();
    void addEnemie3();
    void checkGameOver();
    static void addScore(int increase);
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Map* map;
    QTimer* game_timer;
    QTimer* enemie_timer1;
    QTimer* enemie_timer2;
    QTimer* enemie_timer3;
    int heart;
    static int score;
    QGraphicsTextItem* Heart;
    QGraphicsTextItem* Score;
    QGraphicsTextItem* Money;
    QSound* music;
    QSound* gameOver;
};
#endif // MAINWINDOW_H
