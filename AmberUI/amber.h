#ifndef AMBER_H
#define AMBER_H

#include "common.h"

namespace amber
{

enum Pole
{
    PoleAmber,
    PoleChaos
};

typedef std::map<Pole, int> WorldMap;

struct Amber
{
    int hoursElapsed;

    Pole direction;

    int worldPolePosition;
    WorldMap worldMap;
};

typedef std::function<Amber (const Amber&)> AmberTask;

void changeAmber(const AmberTask& task, Amber& amber);

}

#endif // AMBER_H
