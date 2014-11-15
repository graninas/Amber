#ifndef SHADOWS_H
#define SHADOWS_H

#include "amber.h"
#include "common.h"

namespace shadows
{

using namespace amber;


const AmberTask goNorth = [](const amber::Amber& amber) -> amber::Amber
{
    int northPoleStep = amber.worldMap.at(amber.direction);
    amber::Amber newAmber = amber;
    newAmber.worldPolePosition += northPoleStep;
    return newAmber;
};

const AmberTask tickDay = [](const amber::Amber& amber) -> amber::Amber
{
    amber::Amber newAmber = amber;
    newAmber.hoursElapsed++;
    return newAmber;
};





}

#endif // SHADOWS_H
