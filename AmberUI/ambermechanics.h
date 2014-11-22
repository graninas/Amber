#ifndef AMBERMECHANICS_H
#define AMBERMECHANICS_H

#include "amber.h"
#include "common.h"

namespace amber
{

Amber goDirection(const Amber& amber, Direction::DirectionType dir);
Amber tickHour(const Amber& amber);
Amber stabilizeShadow(const Amber& amber);

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

const AmberTask tickWorldTime = [](const Amber& amber)
{
    return tickHour(amber);
};

const AmberTask shadowStabilization = [](const Amber& amber)
{
    return stabilizeShadow(amber);
};


} // namespace amber

#endif // AMBERMECHANICS_H
