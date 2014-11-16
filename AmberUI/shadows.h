#ifndef SHADOWS_H
#define SHADOWS_H

#include "amber.h"
#include "common.h"

namespace shadows
{

using namespace amber;

Amber updateCurrentShadow(const Amber& amber, Direction::DirectionType dir);
Amber updateCurrentPosition(const Amber& amber);
Amber goDirection(const Amber& amber, Direction::DirectionType dir);

const AmberTask goNorth = [](const Amber& amber) -> Amber
{
    return goDirection(amber, Direction::North);
};

const AmberTask goSouth = [](const Amber& amber) -> Amber
{
    return goDirection(amber, Direction::South);
};

const AmberTask goWest = [](const Amber& amber) -> Amber
{
    return goDirection(amber, Direction::West);
};

const AmberTask goEast = [](const Amber& amber) -> Amber
{
    return goDirection(amber, Direction::East);
};

const AmberTask tickDay = [](const Amber& amber) -> Amber
{
    Amber newAmber = amber;
    newAmber.hoursElapsed++;
    return newAmber;
};





}

#endif // SHADOWS_H
