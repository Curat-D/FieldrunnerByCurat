#ifndef CAR_H
#define CAR_H
#include "tower.h"

class Car : public Tower
{
public:
    Car();
    void advance(int phase) override;
};

#endif // CAR_H
