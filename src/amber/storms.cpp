#include "storms.h"

#include "amberpolearea.h"
#include "shadowmechanics.h"

namespace amber
{

namespace variators
{
const TimedElementVariator SinElementVariator = [](int time, int value, double factor)
{
    return int(sin(time) * value * factor) + value;
};

const TimedElementVariator CosElementVariator = [](int time, int value, double factor)
{
    return int(cos(time) * value * factor) + value;
};
} // namespace variators

// Presentation tip: wrapping lambda into function because C++ doesn't have curring.
// Presentation tip: functions runtime constructing - is completely functional approach.
// Overridding the second argument.
TimedElementVariator sinElementVariator(double factor)
{
    return [&factor](int time, int value, double)
    {
        return variators::SinElementVariator(time, value, factor);
    };
}

TimedElementVariator cosElementVariator(double factor)
{
    return [&factor](int time, int value, double)
    {
        return variators::CosElementVariator(time, value, factor);
    };
}

// Presentation tip: first class funcitons, strategy pattern.
// Presentation tip: functions runtime constructing - is completely functional approach.
// Overridding the second argument.
TimedElementVariator elementVariator(double factor, const TimedElementVariator& function)
{
    return [&factor, &function](int time, int value, double)
    {
        return function(time, value, factor);
    };
}

TimedShadowVariator circullarStormPathVariator(double factor1, double factor2)
{
    TimedShadowVariator variator = [=](const ShadowStructure& structure, int time)
    {
        // Lift 'Safe' concept to monads.
        SafeShadowStructureAction action;
        // Presentation tip: power of combinatorial pattern.
        // You can combine lambdas and regular functions to achieve simplicity.
        action = safeTimedEvalOverElements(time,
            { { Element::Water,  sinElementVariator(factor1) }
            , { Element::Ground, cosElementVariator(-factor1) }
            , { Element::Sky,    elementVariator(factor2,  variators::SinElementVariator) } // N.B., strategy passed.
            , { Element::Air,    elementVariator(-factor2, variators::CosElementVariator) }
            });

        SafeShadowStructure value = runSafe(action, structure);
        if (magic::isFail(value))
        {
            // TODO - fail tolerance, error reporting
            return structure;
        }

        return magic::valueData(value);
    };
    return variator;
}

TimedShadowVariator smallStormPathVariator()
{
    return circullarStormPathVariator(1, 1);
}

TimedShadowVariator bigStormPathVariator()
{
    return circullarStormPathVariator(1, 1);
}

ShadowStructure smallStormStartShadow()
{
    // TODO: move it far from start point.
    return kashfaShadowStructure();
}

ShadowStructure bigStormStartShadow()
{
    // TODO: move it far from start point.
    return kashfaShadowStructure();
}

ShadowStorms storms()
{
    ShadowStorm smallStorm;
    smallStorm.timeToStart = 0;
    smallStorm.timeToLive = std::numeric_limits<int>::max(); // Eternal storms can be done much better.
    smallStorm.innerInfluence = 5;
    smallStorm.outerInfluence = 10;

    smallStorm.pathVariator = smallStormPathVariator();
    smallStorm.currentShadow = smallStormStartShadow();

    ShadowStorm bigStorm;
    bigStorm.timeToStart = 10;
    bigStorm.timeToLive = 300;
    bigStorm.innerInfluence = 30;
    bigStorm.outerInfluence = 50;

    bigStorm.pathVariator = bigStormPathVariator();
    bigStorm.currentShadow = bigStormStartShadow();

    ShadowStorms storms;
    storms.push_back(smallStorm);
    storms.push_back(bigStorm);

    return storms;
}

} // namespace amber
