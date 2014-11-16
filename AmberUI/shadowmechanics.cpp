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

// This boilerplace can be replaced by macro.
SafeShadowStructure safeAirChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::Air, diff);
}

SafeShadowStructure safeSkyChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::Sky, diff);
}

SafeShadowStructure safeWaterChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::Water, diff);
}

SafeShadowStructure safeGroundChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::Ground, diff);
}

SafeShadowStructure safeAmberDistanceChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::AmberDistance, diff);
}

SafeShadowStructure safeChaosDistanceChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::ChaosDistance, diff);
}

SafeShadowStructure safeFloreChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::Flora, diff);
}

SafeShadowStructure safeFaunaChange(const ShadowStructure& structure, int diff)
{
    return safeElementChange(structure, Element::Fauna, diff);
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
