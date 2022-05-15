#ifndef CAR_H
#define CAR_H
#include "tower.h"

class Barrier : public Tower
{
public:
    Barrier();
    ~Barrier();
    void advance(int phase) override;
    void UpGrade() override{};
};

#endif // CAR_H
