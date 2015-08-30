#include "shadowmechanics.h"

namespace amber
{

SafeShadowStructure safeWrap(const ShadowStructure& data)
{
    return magic::success(data);
}

SafeShadowStructure safeBind(const SafeShadowStructure value, const SafeShadowStructureAction& action)
{
    if (value.result == magic::Result::Success)
        return action(value.data);
    return value;
}

SafeShadowStructure runSafe(const SafeShadowStructureAction& action, const ShadowStructure& data)
{
    return action(data);
}

SafeShadowStructure safeElementChange(const ShadowStructure& structure, Element::ElementType elem, int diff)
{
    ShadowStructure newStructure = structure;
    ShadowStructure::iterator it = newStructure.find(elem);

    if (it == newStructure.end())
        return magic::fail(structure);

    it->second += diff;
    return magic::success(newStructure);
}

SafeShadowStructure safeTimedElementChange(const ShadowStructure& structure,
                                           int time,
                                           Element::ElementType elem,
                                           const TimedElementVariator& variator)
{
    ShadowStructure newStructure = structure;
    ShadowStructure::iterator it = newStructure.find(elem);

    if (it == newStructure.end())
        return magic::fail(structure);

    it->second = variator(time, it->second, 1);
    return magic::success(newStructure);
}

SafeShadowStructureAction safeChangeElements(const ElementModifiers& modifiers)
{
    // N.B., modifiers passing by value. Otherwise, this code will cause access violation
    // because of destructing externally defined modifiers.
    SafeShadowStructureAction action = [=](const ShadowStructure& income)
    {
        SafeShadowStructure value = safeWrap(income);
        std::for_each(modifiers.begin(), modifiers.end(), [&value](const ElementModifiers::value_type& modifier)
        {
            value = safeBind(value, [&modifier](const ShadowStructure& structure)
            {
                return safeElementChange(structure, modifier.first, modifier.second);
            });
        });
        return value;
    };

    return action;
}

// TODO: this code is very like the code above.
SafeShadowStructureAction safeTimedEvalOverElements(int time, const TimedElementVariators& variators)
{
    // N.B., variators passing by value. Otherwise, this code will cause access violation
    // because of destructing externally defined variators.
    SafeShadowStructureAction action = [variators, time](const ShadowStructure& income)
    {
        SafeShadowStructure value = safeWrap(income);
        std::for_each(variators.begin(), variators.end(),
                      [&value, variators, time](const TimedElementVariators::value_type& variator)
        {
            value = safeBind(value, [&variator, time](const ShadowStructure& structure)
            {
                return safeTimedElementChange(structure, time, variator.first, variator.second);
            });
        });
        return value;
    };

    return action;
}

double shadowDistance(const ShadowStructure& shadow1, const ShadowStructure& shadow2)
{
    // TODO: do it safe.

    int d1 = shadow1.at(Element::Air)           - shadow2.at(Element::Air);
    int d2 = shadow1.at(Element::Ground)        - shadow2.at(Element::Ground);
    int d3 = shadow1.at(Element::Water)         - shadow2.at(Element::Water);
    int d4 = shadow1.at(Element::Sky)           - shadow2.at(Element::Sky);
    int d5 = shadow1.at(Element::AmberDistance) - shadow2.at(Element::AmberDistance);
    int d6 = shadow1.at(Element::ChaosDistance) - shadow2.at(Element::ChaosDistance);
    int d7 = shadow1.at(Element::Fauna)         - shadow2.at(Element::Fauna);
    int d8 = shadow1.at(Element::Flora)         - shadow2.at(Element::Flora);

    return sqrt(d1*d1 + d2*d2 + d3*d3 + d4*d4 +
                d5*d5 + d6*d6 + d7*d7 + d8*d8);
}

double elementalDistance(const ShadowStructure& shadow1, const ShadowStructure& shadow2)
{
    // TODO: do it safe.

    int d1 = shadow1.at(Element::Air)           - shadow2.at(Element::Air);
    int d2 = shadow1.at(Element::Ground)        - shadow2.at(Element::Ground);
    int d3 = shadow1.at(Element::Water)         - shadow2.at(Element::Water);
    int d4 = shadow1.at(Element::Sky)           - shadow2.at(Element::Sky);
    int d5 = shadow1.at(Element::Fauna)         - shadow2.at(Element::Fauna);
    int d6 = shadow1.at(Element::Flora)         - shadow2.at(Element::Flora);

    return sqrt(d1*d1 + d2*d2 + d3*d3 + d4*d4 +
                d5*d5 + d6*d6);
}

namespace element
{

ShadowStructure::value_type AmberDistance(int distance)
{
    return ShadowStructure::value_type(Element::AmberDistance, distance);
}

ShadowStructure::value_type ChaosDistance(int distance)
{
    return ShadowStructure::value_type(Element::ChaosDistance, distance);
}

ShadowStructure::value_type Air(int air)
{
    return ShadowStructure::value_type(Element::Air, air);
}

ShadowStructure::value_type Sky(int sky)
{
    return ShadowStructure::value_type(Element::Sky, sky);
}

ShadowStructure::value_type Ground(int ground)
{
    return ShadowStructure::value_type(Element::Ground, ground);
}

ShadowStructure::value_type Water(int water)
{
    return ShadowStructure::value_type(Element::Water, water);
}

ShadowStructure::value_type Flora(int flora)
{
    return ShadowStructure::value_type(Element::Flora, flora);
}

ShadowStructure::value_type Fauna(int fauna)
{
    return ShadowStructure::value_type(Element::Fauna, fauna);
}


} // namespace element


} // namespace amber
