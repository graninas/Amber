#ifndef AMBER_H
#define AMBER_H

#include "common.h"
#include "shadowstructure.h"

namespace amber
{

struct Amber
{
    int hoursElapsed;

    Areas areas;

    NearestPlace nearestPlace;
    ShadowStructure playerShadowStructure;
};

typedef std::function<Amber (const Amber&)> AmberTask;

Amber defaultAmber();

}

#endif // AMBER_H
