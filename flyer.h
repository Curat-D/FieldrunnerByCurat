#ifndef FLYER_H
#define FLYER_H

#include <QMovie>
#include "enemie.h"

class Flyer: public Enemie
{
public:
    Flyer();
    ~Flyer(){}
    void advance(int phase) override;
};

#endif // FLYER_H
