#ifndef AMBER_H
#define AMBER_H

#include "common.h"
#include "shadowstructure.h"

namespace amber
{

struct Amber
{
    int hoursElapsed;

    Areas amberAreas;

    // This is an obsolete part.
    Pole::PoleType direction;
    int worldPolePosition;

};

typedef std::function<Amber (const Amber&)> AmberTask;

void changeAmber(const AmberTask& task, Amber& amber);

}

#endif // AMBER_H
