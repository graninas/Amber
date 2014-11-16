#ifndef SHADOWMECHANICS_H
#define SHADOWMECHANICS_H

#include "magic.h"

namespace amber
{

magic::Result<ShadowStructure> safeElementChange(ShadowStructure& structure, Element::ElementType elem, int diff);

// This boilerplace can be replaced by macro.
magic::Result<ShadowStructure> safeAirChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeSkyChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeWaterChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeGroundChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeAmberDistanceChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeChaosDistanceChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeFloreChange(ShadowStructure& structure, int diff);
magic::Result<ShadowStructure> safeFaunaChange(ShadowStructure& structure, int diff);

namespace element
{

ShadowStructure::value_type AmberDistance(int distance);
ShadowStructure::value_type ChaosDistance(int distance);
ShadowStructure::value_type Air(int air);
ShadowStructure::value_type Sky(int sky);
ShadowStructure::value_type Ground(int ground);
ShadowStructure::value_type Water(int water);
ShadowStructure::value_type Flora(int flora);
ShadowStructure::value_type Fauna(int fauna);

}


}

#endif // SHADOWMECHANICS_H
