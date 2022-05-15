#ifndef STUBBORNRUNNER_H
#define STUBBORNRUNNER_H
#include <QMovie>
#include "enemie.h"

class StubbornRunner : public Enemie
{
public:
    StubbornRunner();
    ~StubbornRunner(){}
    void advance(int phase) override;
};

#endif // STUBBORNRUNNER_H
