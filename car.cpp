#include "car.h"
#include "towerGolbal.h"
Car::Car():Tower(CAR_ATK,CAR_RATE,CAR_RADIUS,CAR_HP){
    setMovie(CAR);
}

void Car::advance(int phase){
    if(!phase)
        return;
    if(hp<=0){
        delete this;
        return;
    }

}
