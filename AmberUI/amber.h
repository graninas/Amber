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

    AreaName currentArea;
    ShadowName currentShadow;
    ShadowStructure currentWorld;
};

typedef std::function<Amber (const Amber&)> AmberTask;

void changeAmber(const AmberTask& task, Amber& amber);

}

#endif // AMBER_H
