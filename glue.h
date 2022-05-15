#ifndef GLUE_H
#define GLUE_H

#include <QSound>
#include "tower.h"

class Glue : public Tower
{
public:
    Glue();
    ~Glue();
    void advance(int phase) override;
    void UpGrade() override;
private:
    QSound* music;
};

#endif // GLUE_H
