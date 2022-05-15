#ifndef GATTLING_H
#define GATTLING_H
#include <QSound>
#include "tower.h"

class Gattling: public Tower
{
public:
    Gattling();
    ~Gattling();
    void advance(int phase) override;
    void UpGrade() override;
private:
    QSound* music;
};

#endif // GATTLING_H
