#ifndef GATTLING_H
#define GATTLING_H
#include <QSound>
#include "tower.h"

class Gattling: public Tower
{
public:
    Gattling();
    void advance(int phase) override;
private:
    QSound* music;
};

#endif // GATTLING_H
