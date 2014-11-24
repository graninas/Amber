#ifndef STRINGS_H
#define STRINGS_H

#include "amberstructure.h"
#include "naming.h"


namespace strings
{

std::string playerArrivedToPlace(const amber::NearestPlace& nearestPlace);
std::string playerArrivedToArea(const amber::NearestPlace& nearestPlace);
std::string playersShadowStabilizedAt(const amber::ShadowName& name);
std::string playerAffectedByStormAt(const amber::ShadowName& name);


} // namespace strings

#endif // STRINGS_H
