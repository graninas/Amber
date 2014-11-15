#include "assets.h"

namespace amber
{

Amber defaultAmber()
{
    Amber amber;
    amber.hoursElapsed = 0;
    amber.direction = PoleAmber;
    amber.worldPolePosition = 50;

    return amber;
}

}
