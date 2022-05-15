#ifndef RUNNER_H
#define RUNNER_H

#include <QMovie>
#include "enemie.h"

class Runner : public Enemie
{
public:
    Runner();
    ~Runner(){}
    void advance(int phase) override;
};

#endif // RUNNER_H
