#include "storms.h"

#include "amberpolearea.h"

namespace amber
{

namespace variators
{
const TimedElementVariator SinElementVariator = [](int time, double factor)
{
    return int(sin(double(time)) * factor);
};

const TimedElementVariator CosElementVariator = [](int time, double factor)
{
    return int(cos(double(time)) * factor);
};
} // namespace variators

// Presentation tip: wrapping lambda into function because C++ doesn't have curring.
// Presentation tip: functions runtime constructing - is completely functional approach.
// Overridding the second argument.
TimedElementVariator sinElementVariator(double factor)
{
    return [&factor](int time, double)
    {
        return variators::SinElementVariator(time, factor);
    };
}

TimedElementVariator cosElementVariator(double factor)
{
    return [&factor](int time, double)
    {
        return variators::CosElementVariator(time, factor);
    };
}

// Presentation tip: first class funcitons, strategy pattern.
// Presentation tip: functions runtime constructing - is completely functional approach.
// Overridding the second argument.
TimedElementVariator elementVariator(double factor, const TimedElementVariator& function)
{
    return [&factor, &function](int time, double)
    {
        return function(time, factor);
    };
}

ShadowVariator circullarStormMovingPath(double factor1, double factor2)
{
    ShadowVariator variator = [=](const ShadowStructure& structure, Direction::DirectionType)
    {
        return structure;
        /*
        // Lift 'Safe' concept to monads.
        SafeShadowStructureAction action;

        // Presentation tip: power of combinatorial pattern.
        // You can combine lambdas and regular functions to achieve simplicity.
        action = safeTimedEvalOverElements({ { Element::Water,  sinElementVariator(factor1) }
                                           , { Element::Ground, cosElementVariator(-factor1) }

                                           // N.B., strategy passed.
                                           , { Element::Sky,    elementVariator(factor2,  variators::SinElementVariator) }
                                           , { Element::Air,    elementVariator(-factor2, variators::CosElementVariator) }
                                           });

        SafeShadowStructure value = safeWrap(structure);
        value = runSafe(action, structure);
        if (magic::isFail(value))
        {
            // TODO - fail tolerance, error reporting
            return structure;
        }

        return magic::valueData(value);
        */
    };
    return variator;
}

ShadowVariator smallStormMovingPath()
{
    return circullarStormMovingPath(10, 10);
}

ShadowVariator bigStormMovingPath()
{
    return circullarStormMovingPath(30, 40);
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
    qDebug() << "storms begin";
    ShadowStorm smallStorm;
    smallStorm.timeToStart = 0;
    smallStorm.timeToLive = std::numeric_limits<int>::max(); // Eternal storms can be done much better.
    smallStorm.innerInfluence = 5;
    smallStorm.outerInfluence = 10;

    qDebug() << "storms small moving path";
    smallStorm.movingPath = smallStormMovingPath();
    qDebug() << "storms small stomr start shadow";
    smallStorm.currentShadow = smallStormStartShadow();

    ShadowStorm bigStorm;
    bigStorm.timeToStart = 10;
    bigStorm.timeToLive = 300;
    bigStorm.innerInfluence = 30;
    bigStorm.outerInfluence = 50;

    qDebug() << "storms big storm moving path";
    bigStorm.movingPath = bigStormMovingPath();

    qDebug() << "storms big storm shadow";
    bigStorm.currentShadow = bigStormStartShadow();

    qDebug() << "storms";
    ShadowStorms storms;
    qDebug() << "pushing back 1";
    storms.push_back(smallStorm);
    qDebug() << "pushing back 2";
    storms.push_back(bigStorm);

    qDebug() << "storms end";
    return storms;
}

} // namespace amber
