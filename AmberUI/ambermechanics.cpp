#include "ambermechanics.h"

#include "shadowmechanics.h"
#include "monads.h"
#include "functionalutils.h"
#include "strings.h"

namespace amber
{

namespace mb = monad::maybe;

namespace // anonymous
{

// Auxiliary types.
typedef std::pair<Shadow, double> ShadowAndDistance;


const std::function<MaybeShadow(Area, ShadowName)> lookupShadow =
        [](const Area& area, const ShadowName& shadow)
{
    return utils::lookupMap(shadow, area.shadows);
};

MaybeArea lookupNearestArea(const Amber& amber)
{
    return utils::lookupMap(amber.nearestPlace.area, amber.areas);
}

MaybeShadow lookupNearestShadow(const Amber& amber)
{
    MaybeArea mbArea = lookupNearestArea(amber);
    // Presentation tip: poor template types deducing for function bind(). It is requres an explicit types.
    return monad::maybe::bind<Area, Shadow>(mbArea, [&amber](const Area& area)
    {
        return lookupShadow(area, amber.nearestPlace.shadow);
    });
}

monad::MaybeDouble maybeShadowDistance(const ShadowStructure& shadowStructure1, const MaybeShadow& mbShadow)
{
    return monad::maybe::bind<Shadow, double>(mbShadow, [&shadowStructure1](const Shadow& shadow2)
    {
        return monad::maybe::wrap(shadowDistance(shadowStructure1, shadow2.structure));
    });
}

monad::MaybeDouble maybeShadowStructureDistance(const ShadowStructure& shadowStructure1,
                                                const MaybeShadowStructure& mbShadowStructure2)
{
    return monad::maybe::bind<ShadowStructure, double>(mbShadowStructure2,
        [&shadowStructure1](const ShadowStructure& shadowStructure2)
        {
            return monad::maybe::wrap(shadowDistance(shadowStructure1, shadowStructure2));
        });
}

Amber updatePlayerShadowStructure(const Amber& amber, Direction::DirectionType dir)
{
    // TODO: make it safe.
    // TODO: replace by monadic function something like that:
    // MonadicValue<Maybe> area = mbCurrentArea(amber);
    const Area& area = amber.areas.at(amber.nearestPlace.area);
    const Shadow& shadow = area.shadows.at(amber.nearestPlace.shadow);

    Amber newAmber = amber;
    newAmber.playerShadowStructure = shadow.variator(amber.playerShadowStructure, dir);
    return newAmber;
}

Amber updateNearestPlace(const Amber& amber)
{
    // TODO: make it safe.
    // TODO: replace by monadic function something like that:
    // MonadicValue<Maybe> area = mbCurrentArea(amber);
    const Area& area = amber.areas.at(amber.nearestPlace.area);

    ShadowName nearestShadow = "";
    ShadowStructure nearestShadowStructure = amber.playerShadowStructure;
    double nearestDistance = std::numeric_limits<double>::max();

    std::for_each(area.shadows.begin(), area.shadows.end(),
                  [&amber, &nearestDistance, &nearestShadowStructure, &nearestShadow](const Shadows::value_type& shadow)
    {
        double eDistance = elementalDistance(amber.playerShadowStructure, shadow.second.structure);
        if (eDistance < nearestDistance)
        {
            nearestDistance = eDistance;
            nearestShadow = shadow.first;
            nearestShadowStructure = shadow.second.structure;
        }
    });

    Amber newAmber = amber;
    if (nearestDistance != std::numeric_limits<int>::max())
    {
        newAmber.nearestPlace.shadow = nearestShadow;
        if (abs(nearestDistance) < 1)
        {
            newAmber.playerShadowStructure = nearestShadowStructure;
            newAmber.log.push_back(strings::playerArrivedToPlace(newAmber.nearestPlace));
        }
        else
        {
            newAmber.log.push_back(strings::playerArrivedToArea(newAmber.nearestPlace));
        }
    }

    return newAmber;
}

// TODO: this function too complex. Divide it into 2 functions: composeElementalInfluence() and composeVariator().
// Refactor the same code at amberpolearea.cpp.
ShadowVariator composeInfluenceVariator(const ShadowStructure& fromStructure, const ShadowStructure& toStructure)
{
    // TODO: make it safe.
    ShadowStructure elementalInfluence;
    std::for_each(fromStructure.begin(), fromStructure.end(),
                  [&elementalInfluence, &toStructure](const ShadowStructure::value_type& element)
    {
        if (toStructure.at(element.first) < element.second)
            elementalInfluence[element.first] = -1;
        else
            if (toStructure.at(element.first) > element.second)
                elementalInfluence[element.first] = 1;
    });

    return [=](const ShadowStructure& structure, Direction::DirectionType /*dir*/)
    {
        // TODO: refactor this boilerplate.
        SafeShadowStructureAction action = safeChangeElements(elementalInfluence);
        SafeShadowStructure value = runSafe(action, structure);
        if (magic::isFail(value))
        {
            // TODO - fail tolerance, error reporting
            return structure;
        }

        return magic::valueData(value);
    };
}

} // namespace anonymous

namespace workers
{

typedef std::function<MaybeAmber(Amber)> MaybeAmberTask;
typedef std::function<MaybeAmber(ShadowVariator)> MaybeShadowVariatorToAmberTask;
typedef std::function<MaybeShadowVariator(Amber)> MaybeAmberToShadowVariatorTask;

const std::function<MaybeShadowVariator(Shadow)> getShadowVariator =
    [](const Shadow& shadow)
    {
        return mb::just(shadow.variator);
    };

const MaybeAmberTask safeUpdateNearestPlace =
    [](const Amber& amber)
    {
        // TODO: make it safe, but not now (presentation work is needed).
        return mb::just(updateNearestPlace(amber));
    };

MaybeShadowVariator lookupShadowStructureVariator(const Amber& amber)
{
    MaybeShadow mbShadow = lookupNearestShadow(amber);
    return mb::bind(mbShadow, getShadowVariator);
}

const MaybeAmberToShadowVariatorTask lookupShadowVariator =
        [](const Amber& amber)
{
    return lookupShadowStructureVariator(amber);
};

MaybeShadowVariatorToAmberTask applyMovingVariator(const Amber& amber, Direction::DirectionType dir)
{
    return [&amber, dir](const ShadowVariator& variator)
    {
        Amber newAmber = amber;
        newAmber.playerShadowStructure = variator(amber.playerShadowStructure, dir);
        return mb::just(newAmber);
    };
}

MaybeAmberTask safeMovePlayer(Direction::DirectionType dir)
{
    return [=](const Amber& amber)
    {
        MaybeShadowVariator mbVariator = lookupShadowStructureVariator(amber);
        return mb::bind(mbVariator, applyMovingVariator(amber, dir));
    };
}

Amber goDirectionBinded(const Amber& amber, Direction::DirectionType dir)
{
   MaybeAmber mbAmber = mb::just(amber);
   mbAmber = mb::bind(mbAmber, safeMovePlayer(dir));
   mbAmber = mb::bind(mbAmber, safeUpdateNearestPlace);
   return mb::maybe(mbAmber, amber);
}

// Presentation tip: too easy to mistake here. For example, miss mbAmber3:
// auto m4 = mb::bind(mbAmber4, safeUpdateNearestPlace); // Recursion!
// Use stack instead.
Amber goDirectionBinded1(const Amber& amber, Direction::DirectionType dir)
{
   MaybeAmber mbAmber1            = mb::just(amber);
   MaybeShadowVariator mbVariator = mb::bind(mbAmber1,   lookupShadowVariator);
   MaybeAmber mbAmber2            = mb::bind(mbVariator, applyMovingVariator(amber, dir));
   MaybeAmber mbAmber3            = mb::bind(mbAmber2,   safeUpdateNearestPlace);
   return mb::maybe(mbAmber3, amber);
}

// Presentation tip: too easy to mistake here. For example, miss m3:
// auto m4 = mb::bind(m4, safeUpdateNearestPlace); // Recursion!
// Use stack instead.
Amber goDirectionBinded2(const Amber& amber, Direction::DirectionType dir)
{
   auto m1 = mb::just(amber);
   auto m2 = mb::bind(m1, lookupShadowVariator);
   auto m3 = mb::bind(m2, applyMovingVariator(amber, dir));
   auto m4 = mb::bind(m3, safeUpdateNearestPlace);
   return mb::maybe(m4, amber);
}

Amber goDirectionStacked(const Amber& amber, Direction::DirectionType dir)
{
    mb::MaybeActionStack<Amber, ShadowVariator, Amber, Amber>
    stack = bindMany(lookupShadowVariator,
                     applyMovingVariator(amber, dir),
                     safeUpdateNearestPlace);

    MaybeAmber mbAmber = mb::evalMaybes(mb::just(amber), stack);
    return mb::maybe(mbAmber, amber);
}

Amber goDirection(const Amber& amber, Direction::DirectionType dir)
{
    return goDirectionBinded2(amber, dir);
}

Amber tickHour(const Amber &amber)
{
    Amber newAmber = amber;
    newAmber.hoursElapsed++;
    return newAmber;
}

MaybeAmber stabilizeShadow(const Amber& amber)
{
    MaybeShadow mbNearestShadow = lookupNearestShadow(amber);
    monad::MaybeDouble mbDistance = maybeShadowDistance(amber.playerShadowStructure, mbNearestShadow);

    return monad::maybe::bind<ShadowAndDistance, Amber>(monad::maybe::both(mbNearestShadow, mbDistance),
        [&amber](const ShadowAndDistance& shadowAndDistance)
        {
            const Shadow& nearestShadow = shadowAndDistance.first;
            double distance = shadowAndDistance.second;

            if (distance <= nearestShadow.influence)
            {
                ShadowVariator influenceVariator = composeInfluenceVariator(amber.playerShadowStructure, nearestShadow.structure);

                Amber newAmber = amber;
                newAmber.playerShadowStructure = influenceVariator(amber.playerShadowStructure, Direction::North); // Direction doen't matter.
                return monad::maybe::wrap(updateNearestPlace(newAmber));
            }

            return monad::maybe::nothing<Amber>();
        });
}

MaybeAmber inflateShadowStorms(const Amber& amber)
{
    ShadowStorms newStorms;
    std::for_each(amber.storms.begin(), amber.storms.end(), [&amber, &newStorms](const ShadowStorm& storm)
    {
        ShadowStorm newStorm = storm;
        if (storm.timeToStart >= amber.hoursElapsed
            && storm.timeToLive > 0)
        {
            newStorm.timeToLive--;
            newStorm.currentShadow = storm.pathVariator(storm.currentShadow, amber.hoursElapsed);
        };
        newStorms.push_back(storm);
    });

    Amber newAmber = amber;
    newAmber.storms = newStorms;
    return monad::maybe::just(newAmber);
}

MaybeTimedShadowVariator stormOuterInfluence(const ShadowStorm& storm, const Amber& amber)
{
    if (storm.timeToLive > 0
        && storm.timeToStart >= amber.hoursElapsed)
    {
        monad::MaybeDouble mbPlayerDistance = maybeShadowStructureDistance(amber.playerShadowStructure,
                                                                           monad::maybe::just(storm.currentShadow));
        return monad::maybe::bind<double, TimedShadowVariator>(mbPlayerDistance, [&storm](double dist)
        {
            if (dist <= storm.outerInfluence)
                return monad::maybe::just(storm.pathVariator);
            return monad::maybe::nothing<TimedShadowVariator>();
        });
    }

    return monad::maybe::nothing<TimedShadowVariator>();
}

MaybeAmber affectPlayerCurrentShadow(const Amber& amber, const TimedShadowVariator& variator)
{
    Amber newAmber = amber;
    newAmber.playerShadowStructure = variator(amber.playerShadowStructure, amber.hoursElapsed);
    newAmber.log.push_back(strings::playerAffectedByStormAt(amber.nearestPlace.shadow));
    return monad::maybe::just(newAmber);
}

MaybeAmber affectShadowStorms(const Amber& amber)
{
    MaybeAmber mbAmber = monad::maybe::just(amber);
    MaybeAmber newMbAmber = mbAmber;
    bool affected = false;

    std::for_each(amber.storms.begin(), amber.storms.end(),
                  [&newMbAmber, &mbAmber, &affected](const ShadowStorm& storm)
    {
        newMbAmber = monad::maybe::bind<Amber, Amber>(mbAmber, [&storm](const Amber& amber)
        {
            MaybeTimedShadowVariator mbStormInfluence = stormOuterInfluence(storm, amber);
            return monad::maybe::bind<TimedShadowVariator, Amber>(mbStormInfluence,
                                                                  [&amber](const TimedShadowVariator& variator)
            {
                return affectPlayerCurrentShadow(amber, variator);
            });

            return monad::maybe::just(amber);
        });

        // Only affectable storms are counting.
        if (monad::maybe::isJust(newMbAmber))
        {
            affected = true;
            mbAmber = newMbAmber;
        }
    });

    if (affected)
        return mbAmber;
    return monad::maybe::nothing<Amber>();
}

} // namespace workers

} // namespace amber
