#include "event_log.h"


namespace event_log
{

std::string playerArrivedToPlace(const amber::NearestPlace& nearestPlace)
{
    return std::string("Вы прибыли в ") + naming::shadowNameForm3(nearestPlace.shadow) + ".";
}

std::string playerArrivedToArea(const amber::NearestPlace& nearestPlace)
{
    return std::string("Вы находитесь в тенях ") + naming::shadowNameForm1(nearestPlace.shadow) + ".";
}

std::string playersShadowStabilizedAt(const amber::ShadowName &name)
{
    return std::string("Тень стабилизируется к ") + naming::shadowNameForm2(name) + ".";
}

std::string playerAffectedByStormAt(const amber::ShadowName& name)
{
    return std::string("Вы попали в теневую бурю вблизи ") + naming::shadowNameForm1(name) + ".";
}

} // namespace event_log
