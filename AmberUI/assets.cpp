#include "assets.h"

#include "common.h"
#include "amberpolearea.h"

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
    amber.currentArea = AmberPoleArea;
    amber.currentShadow = AmberShadow;
    amber.currentWorld = amberShadowStructure();

    return amber;
}

}
