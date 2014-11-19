#ifndef AMBERMECHANICS_H
#define AMBERMECHANICS_H

#include "amber.h"
#include "common.h"

namespace amber
{

Amber updateCurrentShadow(const Amber& amber, Direction::DirectionType dir);
Amber updateCurrentPosition(const Amber& amber);
Amber goDirection(const Amber& amber, Direction::DirectionType dir);

// This boilerplace can be removed by a macro.
const AmberTask goNorth = [](const Amber& amber)
{
    return goDirection(amber, Direction::North);
};

const AmberTask goSouth = [](const Amber& amber)
{
    return goDirection(amber, Direction::South);
};

const AmberTask goWest = [](const Amber& amber)
{
    return goDirection(amber, Direction::West);
};

const AmberTask goEast = [](const Amber& amber)
{
    return goDirection(amber, Direction::East);
};

const AmberTask goNorthEast = [](const Amber& amber)
{
    return goDirection(amber, Direction::NorthEast);
};

const AmberTask goNorthWest = [](const Amber& amber)
{
    return goDirection(amber, Direction::NorthWest);
};

const AmberTask goSouthEast = [](const Amber& amber)
{
    return goDirection(amber, Direction::SouthEast);
};

const AmberTask goSouthWest = [](const Amber& amber)
{
    return goDirection(amber, Direction::SouthWest);
};

const AmberTask tickDay = [](const Amber& amber)
{
    Amber newAmber = amber;
    newAmber.hoursElapsed++;
    return newAmber;
};


} // namespace amber

#endif // AMBERMECHANICS_H
