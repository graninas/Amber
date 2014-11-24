#include "ambermechanics.h"

#include "shadowmechanics.h"
#include "monads.h"
#include "functionalutils.h"
#include "strings.h"

namespace amber
{

namespace // anonymous
{

// Auxiliary types.
typedef std::pair<Shadow, double> ShadowAndDistance;

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

Amber goDirection(const Amber& amber, Direction::DirectionType dir)
{
    return updateNearestPlace(updatePlayerShadowStructure(amber, dir));
}

Amber tickHour(const Amber &amber)
{
    Amber newAmber = amber;
    newAmber.hoursElapsed++;
    return newAmber;
}

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
    std::for_each(amber.storms.begin(), amber.storms.end(),
                  [&newMbAmber, &mbAmber](const ShadowStorm& storm)
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
            mbAmber = newMbAmber;
    });

    return mbAmber;
}

} // namespace workers

} // namespace amber
