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
    void addEnemie();
    void checkGameOver();
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Map* map;
    QTimer* game_timer;
    QTimer* enemie_timer;
    int heart;
    QSound* music;
    QSound* gameOver;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
