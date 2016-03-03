#include "event_log.h"


namespace event_log
{

std::string playerArrivedToPlace(const amber::NearestPlace& nearestPlace)
{
    return std::string("You have arrived to ") + naming::shadowNameForm3(nearestPlace.shadow) + ".";
}

std::string playerArrivedToArea(const amber::NearestPlace& nearestPlace)
{
    return std::string("You are in the shadows near ") + naming::shadowNameForm1(nearestPlace.shadow) + ".";
}

std::string playersShadowStabilizedAt(const amber::ShadowName &name)
{
    return std::string("Shadow is stabilizing to ") + naming::shadowNameForm2(name) + ".";
}

std::string playerAffectedByStormAt(const amber::ShadowName& name)
{
    return std::string("Shadow storm near ") + naming::shadowNameForm1(name) + ".";
}

} // namespace event_log
