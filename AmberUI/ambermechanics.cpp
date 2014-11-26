#include "ambermechanics.h"

#include "shadowmechanics.h"
#include "monads.h"
#include "functionalutils.h"
#include "strings.h"

#include <memory>

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

namespace experimental
{


namespace LensKind
{
enum LensKindType
{
    Focus,
    Single,
    Multiple
};
}

struct Identity
{
};

template <typename Zoomed1, typename Zoomed2>
struct Lens
{
    LensKind::LensKindType kind;
    std::function<Zoomed2(Zoomed1)> getter;
    std::function<void(Zoomed1&, Zoomed2)> setter;
};

template <typename Zoomed1, typename Zoomed2, typename Zoomed3 = Identity, typename Zoomed4 = Identity>
struct LensStack
{
    Lens<Zoomed1, Zoomed2> lens1;
    Lens<Zoomed2, Zoomed3> lens2;
    Lens<Zoomed3, Zoomed4> lens3;
};

template <typename Focused>
Lens<Focused, Identity> idL()
{
    Lens<Focused, Identity> l;
    l.kind = LensKind::Focus;
    return l;
}

template <typename Zoomed1, typename Zoomed2>
Lens<Zoomed1, Zoomed2>
    lens(const std::function<Zoomed2(Zoomed1)>& getter,
         const std::function<Zoomed1(Zoomed1, Zoomed2)>& setter)
{
    Lens<Zoomed1, Zoomed2> l;
    l.kind = LensKind::Single;
    l.getter = getter;
    l.setter = setter;
    return l;
}

template <typename Zoomed1, typename Zoomed2, typename Zoomed3, typename Zoomed4>
LensStack<Zoomed1, Zoomed2, Zoomed3, Zoomed4>
    zoom(Lens<Zoomed1, Zoomed2> l1
       , Lens<Zoomed2, Zoomed3> l2
       , Lens<Zoomed3, Zoomed4> l3)
{
    LensStack<Zoomed1, Zoomed2,  Zoomed3, Zoomed4> ls;
    ls.lens1 = l1;
    ls.lens2 = l2;
    ls.lens3 = l3;
    return ls;
}

template <typename Zoomed1, typename Zoomed2, typename Zoomed3>
LensStack<Zoomed1, Zoomed2, Zoomed3, Identity>
    zoom(Lens<Zoomed1, Zoomed2> l1
       , Lens<Zoomed2, Zoomed3> l2)
{
    LensStack<Zoomed1, Zoomed2,  Zoomed3, Identity> ls;
    ls.lens1 = l1;
    ls.lens2 = l2;
    ls.lens3 = idL<Zoomed3>();
    return ls;
}

template <typename Zoomed1, typename Zoomed2>
LensStack<Zoomed1, Zoomed2, Identity, Identity>
    zoom(Lens<Zoomed1, Zoomed2> l1)
{
    LensStack<Zoomed1, Zoomed2, Identity, Identity> ls;
    ls.lens1 = l1;
    ls.lens2 = idL<Zoomed2>();
    ls.lens3 = idL<Identity>();
    return ls;
}

template <typename Focused,
          typename Zoomed1,
          typename Zoomed2,
          typename Zoomed3 = Identity,
          typename Zoomed4 = Identity>
monad::maybe::Maybe<Zoomed1> evalLens(const LensStack<Zoomed1, Zoomed2, Zoomed3, Zoomed4>& lensStack,
                                      const Zoomed1& zoomed1,
                                      const std::function<Focused(Focused)>& variator)
{

}

struct InnerStruct
{
    int i;
};

struct Test
{
    InnerStruct inner;
};

typedef monad::MonadicValue<monad::maybe::Maybe<Test>> MaybeTest;

const std::function<int(int)> increaseI = [](int i)
{
    return i++;
};

Lens<Test, InnerStruct> innerL()
{
    return lens<Test, InnerStruct>
            ( [](const Test& t) { return t.inner; }
            , [](const Test& t, const InnerStruct& inner) {
                Test newTest = t;
                newTest.inner = inner;
                return newTest;
            }
    );
}

Lens<InnerStruct, int> intIL()
{
    return lens<InnerStruct, int>
            ( [](const InnerStruct& inner) { return inner.i; }
            , [](const InnerStruct& inner, int i) {
                InnerStruct newInnerStruct = inner;
                newInnerStruct.i = i;
                return newInnerStruct;
            }
        );
}

MaybeTest testLens(const Test& amber)
{
    LensStack<Test, InnerStruct, int> lensStack
       = zoom<Test, InnerStruct, int>(innerL(), intIL());

//    MaybeAmber mbNewAmber = evalLens<int>(lensStack, amber, increaseI);

  //  return mbNewAmber;
}

/*
typedef std::function<ShadowStorm(ShadowStorm)> ShadowStormVariator;

const ShadowStormVariator tickTimeToLive = [](const ShadowStorm& storm)
{
    ShadowStorm newStorm = storm;
    newStorm.timeToLive++;
    return newStorm;
};

Lens shadowStormsL()
{
    return lens( [](const Amber& amber) { return amber.storms; }
               , [](Amber& amber, const ShadowStorms& storms) { amber.storms = storms; }
    );
}

Lens shadowStormL()
{
    return listL<ShadowStorm>();
}

Lens timeToLiveL()
{
    return lens( [](const ShadowStorm& storm) { return storm.timeToLive; }
               , [](ShadowStorm& storm, int ttl) { storm.timeToLive = ttl; }
    );
}

MaybeAmber inflateShadowStorms2(const Amber& amber)
{
    Lens lens = zoom(shadowStormsL(),
                     zoomEvery(shadowStormL(),
                               focus(timeToLiveL())));

    MaybeAmber mbNewAmber = evalLens(lens, amber, tickTimeToLive);

    return mbNewAmber;
}

*/

} // namespace experimental


} // namespace workers
} // namespace amber
