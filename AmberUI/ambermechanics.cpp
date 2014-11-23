#include "ambermechanics.h"

#include "shadowmechanics.h"
#include "monads.h"
#include "functionalutils.h"

namespace amber
{

namespace // anonymous
{

// Auxiliary type.
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
        SafeShadowStructure value = safeWrap(structure);
        value = runSafe(action, structure);
        if (magic::isFail(value))
        {
            // TODO - fail tolerance, error reporting
            return structure;
        }

        return magic::valueData(value);
    };
}

} // namespace anonymous

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
                return monad::maybe::wrap(newAmber);
            }

            return monad::maybe::nothing<Amber>();
        });
}

// Experimental 'lenses-like' design.

namespace experimental
{


namespace lenses
{

template <typename Input, typename Zoomed, typename... Zoomers> struct Lense
{
    std::function<Zoomed(Input)> zoomer;
    Lense<Input, Zoomers...> lenses;
};

template <typename Input, typename Zoomed, typename... Zoomers> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed, Zoomers...>& l, const Input& input)
{
    std::list<Zoomed> zoomed;
    if (sizeof...(Zoomers) == 0)
    {
        zoomed.push_back(l.zoomer(input));
    }
    else
    {
        std::for_each(l.lenses.begin(), l.lenses.end(),
                      [&zoomed, &input](const Lense<Input, Zoomers...>& internalLense)
        {
            std::list<Zoomed> rolledOut = rolloutLense(internalLense, input);
            zoomed.insert(zoomed.end(), rolledOut.begin(), rolledOut.end());
        });
    }
    return zoomed;
}

template <typename Input, typename Zoomed> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed>& l, const Input& input)
{
    std::list<Zoomed> zoomed { l.zoomer(input) };
    return zoomed;
}


template <typename Input, typename Zoomed, typename... Zoomers>
    std::list<Zoomed>
    overLense(const Lense<Input, Zoomed, Zoomers...>& l,
              const Input& input,
              const std::function<Zoomed(Zoomed)>& action)
{
    std::list<Zoomed> zoomed = rolloutLense(l, input);
    std::transform(zoomed.begin(), zoomed.end(), zoomed.begin(), action);
    return zoomed;
}

/*
template <typename Input, typename Zoomed, typename... Zoomers> struct Lense
{
    std::function<Zoomed(Input)> zoomer;
    Lense<Input, Zoomers...> lenses;
};

template <typename Input, typename Zoomed, typename... Zoomers> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed, Zoomers...>& l, const Input& input)
{
    std::list<Zoomed> zoomed;
    if (sizeof...(Zoomers) == 0)
    {
        zoomed.push_back(l.zoomer(input));
    }
    else
    {
        std::for_each(l.lenses.begin(), l.lenses.end(),
                      [&zoomed, &input](const Lense<Input, Zoomers...>& internalLense)
        {
            std::list<Zoomed> rolledOut = rolloutLense(internalLense, input);
            zoomed.insert(zoomed.end(), rolledOut.begin(), rolledOut.end());
        });
    }
    return zoomed;
}

template <typename Input, typename Zoomed> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed>& l, const Input& input)
{
    std::list<Zoomed> zoomed { l.zoomer(input) };
    return zoomed;
}


template <typename Input, typename Zoomed, typename... Zoomers>
    std::list<Zoomed>
    overLense(const Lense<Input, Zoomed, Zoomers...>& l,
              const Input& input,
              const std::function<Zoomed(Zoomed)>& action)
{
    std::list<Zoomed> zoomed = rolloutLense(l, input);
    std::transform(zoomed.begin(), zoomed.end(), zoomed.begin(), action);
    return zoomed;
}
*/
    /*
    template <typename Input, typename Output> Lense<Input, Output> lense(const Input& input)
    {
        Lense<Input> l;
        l.kind = LenseKind::Regular;
        l.value = input;
        return l;
    }
*/


} // namespace lenses

typedef lenses::Lense<Amber, ShadowStorms> ShadowStormsLense;
typedef lenses::Lense<ShadowStorms, ShadowStorm> ShadowStormLense;

ShadowStormsLense shadowStormsLense()
{
    lenses::Lense<Amber, ShadowStorms, ShadowStorm> l;
    l.zoomer = [](const Amber& amber)
    {
        return amber.storms;
    };
    return l;
}
/*
const ShadowStormLense shadowStormLense = [](const ShadowStorms& storms)
{
    return lenseEach<ShadowStorms, ShadowStorm>(storms);
};


const ShadowStorm moveShadowStorm = [](const ShadowStorm& storm)
{
    // TODO
    return storm;
};
*/

//zoom<Amber, ShadowStorms>(shadowStormsLense, zoom<ShadowStorms, ShadowStorm>(shadowStormLense, idLense)

} // namespace experimental




MaybeAmber inflateShadowStorms(const Amber& amber)
{
    /*
    MaybeShadowStorms mbShadowStorms = bind<Amber, ShadowStorms>(monad::maybe::just(amber),
        [](const Amber& a)
        {
            return overLense<Amber, ShadowStorms, ShadowStorm>(shadowStormsLense, a, moveShadowStorm);
        });
    // TODO
    */
    return monad::maybe::wrap(amber);
}

} // namespace amber
