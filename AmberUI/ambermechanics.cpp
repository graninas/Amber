#include "ambermechanics.h"

#include "shadowmechanics.h"

namespace amber
{

Amber updateCurrentShadow(const Amber& amber, Direction::DirectionType dir)
{
    // TODO: make it safe.
    Amber newAmber = amber;
    const Area& area = amber.areas.at(amber.position.area);
    const Shadow& shadow = area.shadows.at(amber.position.shadow);
    newAmber.currentShadowStructure = shadow.variator(amber.currentShadowStructure, dir);
    return newAmber;
}

Amber updateCurrentPosition(const Amber& amber)
{
    // TODO: make it safe.
    const Area& area = amber.areas.at(amber.position.area);

    ShadowName nearestShadow = "";
    double nearestDistance = std::numeric_limits<double>::max();

    std::for_each(area.shadows.begin(), area.shadows.end(), [&amber, &nearestDistance, &nearestShadow](const Shadows::value_type& shadow)
    {
        double distance = shadowDistance(amber.currentShadowStructure, shadow.second.structure);
        if (distance < nearestDistance)
        {
            nearestDistance = distance;
            nearestShadow = shadow.first;
        }
    });

    Amber newAmber = amber;
    if (nearestDistance != std::numeric_limits<int>::max())
        newAmber.position.shadow = nearestShadow;

    return newAmber;
}

Amber goDirection(const Amber& amber, Direction::DirectionType dir)
{
    return updateCurrentPosition(updateCurrentShadow(amber, dir));
}

} // namespace amber
