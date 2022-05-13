#ifndef CAR_H
#define CAR_H
#include "tower.h"

class Barrier : public Tower
{
public:
    Barrier();
    ~Barrier();
    void advance(int phase) override;
};

#endif // CAR_H
