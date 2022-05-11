#ifndef GLUE_H
#define GLUE_H

#include <QSound>
#include "tower.h"

class Glue : public Tower
{
public:
    Glue();
    void advance(int phase) override;
private:
    QSound* music;
};

#endif // GLUE_H
