#ifndef EVENT_LOG
#define EVENT_LOG

#include "amberstructure.h"
#include "naming.h"


namespace event_log
{

std::string playerArrivedToPlace(const amber::NearestPlace& nearestPlace);
std::string playerArrivedToArea(const amber::NearestPlace& nearestPlace);
std::string playersShadowStabilizedAt(const amber::ShadowName& name);
std::string playerAffectedByStormAt(const amber::ShadowName& name);


} // namespace event_log

#endif // EVENT_LOG
