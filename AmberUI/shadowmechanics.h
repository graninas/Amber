#ifndef SHADOWMECHANICS_H
#define SHADOWMECHANICS_H

#include "magic.h"

namespace amber
{

typedef magic::Value<ShadowStructure> SafeShadowStructure;
typedef std::function<SafeShadowStructure(ShadowStructure)> SafeShadowStructureAction;

SafeShadowStructure safeWrap(const ShadowStructure& data);
SafeShadowStructure safeBind(const SafeShadowStructure value, const SafeShadowStructureAction& action);
SafeShadowStructure runSafe(const SafeShadowStructureAction& action, const ShadowStructure& data);

// Presentation tip: monadic functions.
SafeShadowStructure safeElementChange(const ShadowStructure& structure, Element::ElementType elem, int diff);

typedef ShadowStructure ElementModifiers;
SafeShadowStructureAction safeChangeElements(const ElementModifiers &modifiers);

double shadowDistance(const ShadowStructure& shadow1, const ShadowStructure& shadow2);


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
