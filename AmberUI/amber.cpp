#include "amber.h"

#include "amberpolearea.h"
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
    Amber amber;
    amber.hoursElapsed = 0;
    amber.areas = areas();
    amber.nearestPlace.area = AmberPoleArea;
    amber.nearestPlace.shadow = BergmaShadow;
    amber.playerShadowStructure = bergmaShadowStructure();

    return amber;
}

}
