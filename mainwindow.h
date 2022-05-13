#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QSound>
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void advanceBulllet();
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Map* map;
    QTimer* game_timer;
    QTimer* enemie_timer1;
    QTimer* enemie_timer2;
    QTimer* enemie_timer3;
    int heart;
    QSound* music;
    QSound* gameOver;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
