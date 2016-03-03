#ifndef SHADOWMECHANICS_H
#define SHADOWMECHANICS_H

#include "taskmechanics.h"

namespace amber
{

// TODO: unify 'Safe' concept and Maybe monad.
typedef Value<ShadowStructure> SafeShadowStructure;
typedef std::function<SafeShadowStructure(ShadowStructure)> SafeShadowStructureAction;

typedef ShadowStructure ElementModifiers;
typedef std::function<int(int, int, double)> TimedElementVariator;
typedef std::map<Element::ElementType, TimedElementVariator> TimedElementVariators;

SafeShadowStructure safeWrap(const ShadowStructure& data);
SafeShadowStructure safeBind(const SafeShadowStructure value, const SafeShadowStructureAction& action);
SafeShadowStructure runSafe(const SafeShadowStructureAction& action, const ShadowStructure& data);

SafeShadowStructure safeElementChange(const ShadowStructure& structure, Element::ElementType elem, int diff);
SafeShadowStructure safeTimedElementChange(const ShadowStructure& structure,
                                           int time,
                                           Element::ElementType elem,
                                           const TimedElementVariator &variator);

SafeShadowStructureAction safeChangeElements(const ElementModifiers &modifiers);
SafeShadowStructureAction safeTimedEvalOverElements(int time, const TimedElementVariators& variators);

double shadowDistance(const ShadowStructure& shadow1, const ShadowStructure& shadow2);
double elementalDistance(const ShadowStructure& shadow1, const ShadowStructure& shadow2);


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

} // namespace element

} // namespace amber

#endif // SHADOWMECHANICS_H
