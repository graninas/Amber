#include "shadowmechanics.h"

namespace amber
{

magic::Result<ShadowStructure> safeElementChange(ShadowStructure& structure, Element::ElementType elem, int diff)
{
    ShadowStructure newStructure = structure;
    ShadowStructure::iterator it = newStructure.find(elem);

    if (it == newStructure.end())
        return magic::failResult(structure);

    *it += diff;
    return magic::successResult(newStructure);
}

// This boilerplace can be replaced by macro.
magic::Result<ShadowStructure> safeAirChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::Air, diff);
}

magic::Result<ShadowStructure> safeSkyChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::Sky, diff);
}

magic::Result<ShadowStructure> safeWaterChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::Water, diff);
}

magic::Result<ShadowStructure> safeGroundChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::Ground, diff);
}

magic::Result<ShadowStructure> safeAmberDistanceChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::AmberDistance, diff);
}

magic::Result<ShadowStructure> safeChaosDistanceChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::ChaosDistance, diff);
}

magic::Result<ShadowStructure> safeFloreChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::Flore, diff);
}

magic::Result<ShadowStructure> safeFaunaChange(ShadowStructure& structure, int diff)
{
    return safeStructureChange(structure, Element::Fauna, diff);
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
