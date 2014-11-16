#include "shadows.h"

namespace shadows
{

Amber updateCurrentShadow(const Amber& amber, Direction::DirectionType dir)
{
    Amber newAmber = amber;
    const Area& area = amber.areas.at(amber.position.area);
    const Shadow& shadow = area.shadows.at(amber.position.shadow);
    newAmber.currentShadowStructure = shadow.variator(amber.currentShadowStructure, dir);
    return newAmber;
}

Amber updateCurrentPosition(const Amber& amber)
{
    Amber newAmber = amber;
    const Area& area = amber.areas.at(amber.position.area);
    ShadowPaths::const_iterator shadowPathIt = area.paths.find(newAmber.currentShadowStructure);
    if (shadowPathIt != area.paths.end())
    {
        newAmber.position.area = shadowPathIt->second.area;
        newAmber.position.shadow = shadowPathIt->second.shadow;
    }
    return newAmber;
}

Amber goDirection(const Amber& amber, Direction::DirectionType dir)
{
    return updateCurrentPosition(updateCurrentShadow(amber, dir));
}

}
