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
//    amber.direction = PoleAmber;
//    amber.worldPolePosition = 50;
    return amber;
}

}
