#include "amber.h"

#include "amberpolearea.h"
#include "storms.h"
#include "knownareas.h"

namespace amber
{

Areas areas()
{
    return {
        { AmberPoleArea, amberPoleArea() }
    };
}

Amber defaultAmber()
{
    qDebug() << "default amber";
    Amber amber;
    amber.hoursElapsed = 0;
    amber.areas = areas();
    amber.storms = storms();
    amber.nearestPlace.area = AmberPoleArea;
    amber.nearestPlace.shadow = BergmaShadow;
    amber.playerShadowStructure = bergmaShadowStructure();

    qDebug() << "end of default amber";
    return amber;
}

} // namespace amber
