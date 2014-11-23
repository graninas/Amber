#include "storms.h"

#include "amberpolearea.h"

namespace amber
{

namespace variators
{
const ElementVariator SinElementVariator = [](int value, double factor)
{
    return int(sin(double(value)) * factor);
};

const ElementVariator CosElementVariator = [](int value, double factor)
{
    return int(cos(double(value)) * factor);
};
} // namespace variators

// Presentation tip: wrapping lambda into function because C++ doesn't have curring.
// Presentation tip: functions runtime constructing - is completely functional approach.
// Overridding the second argument.
ElementVariator sinElementVariator(double factor)
{
    return [&factor](int value, double)
    {
        return variators::SinElementVariator(value, factor);
    };
}

ElementVariator cosElementVariator(double factor)
{
    return [&factor](int value, double)
    {
        return variators::CosElementVariator(value, factor);
    };
}

// Presentation tip: first class funcitons, strategy pattern.
// Presentation tip: functions runtime constructing - is completely functional approach.
// Overridding the second argument.
ElementVariator elementVariator(double factor, const ElementVariator& function)
{
    return [&factor, &function](int value, double)
    {
        return function(value, factor);
    };
}

ShadowVariator smallStormMovingPath()
{
    ShadowVariator variator = [=](const ShadowStructure& structure, Direction::DirectionType)
    {
        // Lift 'Safe' concept to monads.
        SafeShadowStructureAction action;

        // Presentation tip: power of combinatorial pattern.
        // You can combine lambdas and regular functions to achieve simplicity.
        action = safeEvalOverElements({ { Element::Water,  sinElementVariator(10) }
                                      , { Element::Ground, cosElementVariator(-10) }

                                      // N.B., strategy passed.
                                      , { Element::Sky,    elementVariator(10,  variators::SinElementVariator) }
                                      , { Element::Air,    elementVariator(-10, variators::CosElementVariator) }
                                      });

        SafeShadowStructure value = safeWrap(structure);
        value = runSafe(action, structure);
        if (magic::isFail(value))
        {
            // TODO - fail tolerance, error reporting
            return structure;
        }

        return magic::valueData(value);
    };
    return variator;
}

ShadowStructure smallStormStartShadow()
{
    // TODO: move it far from start point.
    return kashfaShadowStructure();
}

ShadowStorms storms()
{
    ShadowStorm smallStorm;
    smallStorm.timeToLive = std::numeric_limits<int>::max(); // Eternal storms can be done much better.
    smallStorm.innerInfluence = 5;
    smallStorm.outerInfluence = 10;
    smallStorm.movingPath = smallStormMovingPath();
    smallStorm.currentShadow = smallStormStartShadow();

    ShadowStorms storms;
    storms.push_back(smallStorm);
    return storms;
}

} // namespace amber
