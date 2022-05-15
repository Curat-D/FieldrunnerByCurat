#include "tower.h"
#include "map.h"
#include "runner.h"
#include "enemieGlobal.h"
#include "global.h"
#include <QDebug>
Runner::Runner():Enemie(RunnerHp, RunnerAtkToTower, RunnerAtkToHeart,RunnerSpeed, RunnerRadius, RunnerInterval, RunnerHeight, RunnerWidth){
    setMoive(RunnerRight);
}

void Runner::advance(int phase){
    if (!phase)
        return;
    update();
    count++;
    if(hp<=0){
        delete this;
        return;
    }
    if(count==interval){
        QList<QGraphicsItem *> items = collidingItems();
        if(!items.isEmpty()){
            Tower* tower = qgraphicsitem_cast<Tower*>(items[0]);
            tower->BeAttacked(atkToTower);
        }
        count=0;
    }

  //  qDebug()<<actualSpeed;
    QPoint pos(x(),y());
    QPoint new_pos = Map::advanceGroundPath(state,pos,actualSpeed);
 //   qDebug()<<"原来："<<pos;
 //   qDebug()<<"现在："<<new_pos;
 //   qDebug()<<"";

/*    qDebug()<<preState;
    qDebug()<<x()<<" "<<y()<<" "<<new_pos.x()<<" "<<new_pos.y();
    qDebug()<<"";*/
    setPos(new_pos);
    if(new_pos.x()>pos.x()){
        if(preState!=enemie_right){
            setMoive(RunnerRight);
            preState=enemie_right;
        }
    }
    else if(new_pos.x()<pos.x()){
        if(preState!=enemie_left){
            setMoive(RunnerLeft);
            preState=enemie_left;
        }
    }
    else if(new_pos.y()>pos.y()){
        if(preState!=enemie_down){
            setMoive(RunnerDown);
            preState=enemie_down;
        }
    }
    else if(new_pos.y()<pos.y()){
        if(preState!=enemie_up){
            setMoive(RunnerUp);
            preState=enemie_up;
        }
    }
    return;

   /* if(x()<TRUN_ONE_X && state<=1)
        state = 1;
    else if(x()<TRUN_TWO_X && state<=2)
        state = 2;
    else if(x()==TRUN_THREE_X && y()>TRUN_THREE_Y && state<=3)
        state = 3;
    else if(x()<TRUN_FOUR_X && y()==TRUN_FOUR_Y && state<=4)
        state = 4;
    else if(x()==TRUN_FIVE_X && y()<TRUN_FIVE_Y && state <= 5)
        state = 5;
    else if(x()>TRUN_SIX_X && y()==TRUN_SIX_Y && state<=6)
        state = 6;
    else if(x()==TRUN_SEVEN_X && y()>TRUN_SEVEN_Y && state<=7)
        state = 7;

    else if(x()<2*TRUN_MIDDLE_X-TRUN_SEVEN_X && y()==TRUN_SEVEN_Y && state<=8)
        state = 8;
    else if(x()==2*TRUN_MIDDLE_X-TRUN_SIX_X && y()<TRUN_SIX_Y && state<=9)
        state = 9;
    else if(x()>2*TRUN_MIDDLE_X-TRUN_FIVE_X && y()==TRUN_FIVE_Y && state<=10)
        state=10;
    else if(x()==2*TRUN_MIDDLE_X-TRUN_FOUR_X && y()>TRUN_FOUR_Y && state<=11)
        state=11;
    else if(x()<2*TRUN_MIDDLE_X-TRUN_THREE_X && y()==TRUN_THREE_Y && state<=12)
        state=12;
    else if(x()==2*TRUN_MIDDLE_X-TRUN_TWO_X && y()<TRUN_TWO_Y && state<=13)
        state=13;
    else if(x()<2*TRUN_MIDDLE_X-TRUN_ONE_X && y()<TRUN_ONE_Y && state<=14)
        state=14;
    else
        state=15;
    switch(state){
    case 1:case 4:case 8:case 12:case 15:
        if(preState!=enemie_right){
            setMoive(RunnerRight);
            preState=enemie_right;
        }
        setX(x() + speed);
        break;
    case 6:case 10:
        if(preState!=enemie_left){
            setMoive(RunnerLeft);
            preState=enemie_left;
        }
        setX(x() - speed);
        break;
    case 3:case 7:case 11:
        if(preState!=enemie_up){
            setMoive(RunnerUp);
            preState=enemie_up;
        }
        setY(y() - speed);
        break;
    case 5:case 9:case 13:
        if(preState!=enemie_down){
            setMoive(RunnerDown);
            preState=enemie_down;
        }
        setY(y() + speed);
        break;
    case 2:
        if(preState!=enemie_right_up){
            setMoive(RunnerRight);
            preState=enemie_right_up;
        }
        setX(x() + speed/2);
        setY(y() - speed/2);
        break;
    case 14:
        if(preState!=enemie_right_down){
            setMoive(RunnerRight);
            preState=enemie_right_down;
        }
        setX(x() + speed/2);
        setY(y() + speed/2);
        break;
    default:
        break;
    }*/

}
