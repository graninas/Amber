#include "ambermechanics.h"

#include "shadowmechanics.h"
#include "monad.h"

#include <QDebug>

namespace amber
{

namespace // anonymous
{

Amber updateCurrentShadow(const Amber& amber, Direction::DirectionType dir)
{
    // TODO: make it safe.
    // TODO: replace by monadic function something like that:
    // GenericValue<Maybe> area = mbCurrentArea(amber);
    const Area& area = amber.areas.at(amber.position.area);
    const Shadow& shadow = area.shadows.at(amber.position.shadow);

    Amber newAmber = amber;
    newAmber.currentShadowStructure = shadow.variator(amber.currentShadowStructure, dir);
    return newAmber;
}

// TODO: update current shadow structure!
Amber updateCurrentPosition(const Amber& amber)
{
    // TODO: make it safe.
    // TODO: replace by monadic function something like that:
    // GenericValue<Maybe> area = mbCurrentArea(amber);
    const Area& area = amber.areas.at(amber.position.area);

    ShadowName nearestShadow = "";
    double nearestDistance = std::numeric_limits<double>::max();

    std::for_each(area.shadows.begin(), area.shadows.end(), [&amber, &nearestDistance, &nearestShadow](const Shadows::value_type& shadow)
    {
        double distance = shadowDistance(amber.currentShadowStructure, shadow.second.structure);
        qDebug() << "Distance (" << QString::fromStdString(shadow.first) << "):" << distance;
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

// TODO: this function too complex. Divide it into 2 functions: composeElementalInfluence() and composeVariator().
// Refactor the same code at amberpolearea.cpp.
ShadowVariator composeInfluenceVariator(const ShadowStructure& fromStructure, const ShadowStructure& toStructure)
{
    // TODO: make it safe.
    ShadowStructure elementalInfluence;
    std::for_each(fromStructure.begin(), fromStructure.end(),
                  [&elementalInfluence, &toStructure](const ShadowStructure::value_type& element)
    {
        if (toStructure.at(element.first) < element.second)
            elementalInfluence[element.first] = -1;
        else
            if (toStructure.at(element.first) > element.second)
                elementalInfluence[element.first] = 1;
    });

    return [=](const ShadowStructure& structure, Direction::DirectionType /*dir*/)
    {
        // TODO: refactor this boilerplate.
        SafeShadowStructureAction action = safeChangeElements(elementalInfluence);
        SafeShadowStructure value = safeWrap(structure);
        value = runSafe(action, structure);
        if (magic::isFail(value))
        {
            // TODO - fail tolerance, error reporting
            return structure;
        }

        return magic::valueData(value);
    };
}

} // namespace anonymous

Amber goDirection(const Amber& amber, Direction::DirectionType dir)
{
    return updateCurrentPosition(updateCurrentShadow(amber, dir));
}

Amber tickHour(const Amber &amber)
{
    Amber newAmber = amber;
    newAmber.hoursElapsed++;
    return newAmber;
}

Amber stabilizeShadow(const Amber& amber)
{
    // TODO: make it safe.
    // TODO: replace by monadic function something like that:
    // GenericValue<Maybe> area = mbCurrentArea(amber);
    const Area& area = amber.areas.at(amber.position.area);
    const Shadow& nearestShadow = area.shadows.at(amber.position.shadow);

    double distance = shadowDistance(amber.currentShadowStructure, nearestShadow.structure);

    if (distance <= nearestShadow.influence)
    {
        qDebug() << "Activating influence of " << QString::fromStdString(amber.position.shadow);
        ShadowVariator influenceVariator = composeInfluenceVariator(amber.currentShadowStructure, nearestShadow.structure);

        // TODO: refactor the same code at the begining of abmermechanics.cpp.
        Amber newAmber = amber;
        newAmber.currentShadowStructure = influenceVariator(amber.currentShadowStructure, Direction::North); // Direction doen't matter.
        return newAmber;
    }

    return amber;
}

} // namespace amber
