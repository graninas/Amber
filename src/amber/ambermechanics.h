#ifndef AMBERMECHANICS_H
#define AMBERMECHANICS_H

#include "amber.h"
#include "taskmechanics.h"

#include <monads.h>

namespace amber
{

typedef monad::maybe::Maybe<Amber> MaybeAmber;
typedef monad::maybe::Maybe<Area> MaybeArea;
typedef monad::maybe::Maybe<Shadow> MaybeShadow;
typedef monad::maybe::Maybe<ShadowStructure> MaybeShadowStructure;
typedef monad::maybe::Maybe<ShadowVariator> MaybeShadowVariator;
typedef monad::maybe::Maybe<ShadowStorm> MaybeShadowStorm;
typedef monad::maybe::Maybe<ShadowStorms> MaybeShadowStorms;
typedef monad::maybe::Maybe<TimedShadowVariator> MaybeTimedShadowVariator;

namespace workers
{

Amber goDirection(const Amber& amber, Direction::DirectionType dir);
Amber tickHour(const Amber& amber);
MaybeAmber stabilizeShadow(const Amber& amber);
MaybeAmber inflateShadowStorms(const Amber& amber);
MaybeAmber affectShadowStorms(const Amber& amber);

} // namespace workers

// This boilerplace can be removed by a macro.
const AmberTask goNorth = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::North);
};

const AmberTask goSouth = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::South);
};

const AmberTask goWest = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::West);
};

const AmberTask goEast = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::East);
};

const AmberTask goNorthEast = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::NorthEast);
};

const AmberTask goNorthWest = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::NorthWest);
};

const AmberTask goSouthEast = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::SouthEast);
};

const AmberTask goSouthWest = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::SouthWest);
};

const AmberTask tickWorldTime = [](const Amber& amber)
{
    return workers::tickHour(amber);
};

const AmberTask shadowStabilization = [](const Amber& amber)
{
    return monad::maybe::maybe(workers::stabilizeShadow(amber), amber);
};

const AmberTask inflateShadowStorms = [](const Amber& amber)
{
    return monad::maybe::maybe(workers::inflateShadowStorms(amber), amber);
};

const AmberTask affectShadowStorms = [](const Amber& amber)
{
    MaybeAmber mbAmber = workers::affectShadowStorms(amber);
    if (monad::maybe::isNothing(mbAmber))
    {
        throw std::domain_error("Storm has no effect"); // This is a very, very bad design. Just a showcase.
    }
    return monad::maybe::maybe(mbAmber, amber);
};


const AmberTask tickOneAmberHour = [](const amber::Amber& amber)
{
    auto a1 = anyway(inflateShadowStorms, pure(amber));
    //auto a2 = anyway(affectShadowStorms, a1);
    auto a3 = anyway(shadowStabilization, a1);
    auto a4 = anyway(tickWorldTime, a3);
    return a4.amber;
};

const AmberTask sleep8hours = [](const amber::Amber& amber)
{
    auto res = times(8, tickOneAmberHour, pure(amber));
    return res.amber;
};

} // namespace amber

#endif // AMBERMECHANICS_H
