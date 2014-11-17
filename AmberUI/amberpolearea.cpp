#include "amberpolearea.h"

#include "common.h"
#include "shadowmechanics.h"
#include "knownareas.h"

namespace amber
{

// Presentation tip: the map of Amber can be shown.
ShadowStructure trueAmberStructure()
{
    return {
        element::AmberDistance(0)
      , element::ChaosDistance(100)
      , element::Ground(90)
      , element::Water(10)
      , element::Air(100)
      , element::Sky(70)
      , element::Flora(100)
      , element::Fauna(100)
    };
}

ShadowStructure amberShadowStructure()
{
    return {
        element::AmberDistance(1)
      , element::ChaosDistance(99)
      , element::Ground(70)
      , element::Water(30)
      , element::Air(100)
      , element::Sky(70)
      , element::Flora(100)
      , element::Fauna(100)
    };
}

ShadowStructure bergmaShadowStructure()
{
    return {
        element::AmberDistance(2)
      , element::ChaosDistance(98)
      , element::Ground(40)
      , element::Water(60)
      , element::Air(90)
      , element::Sky(80)
      , element::Flora(100)
      , element::Fauna(100)
    };
}

ShadowStructure trueBergmaStructure()
{
    return {
        element::AmberDistance(3)
      , element::ChaosDistance(97)
      , element::Ground(30)
      , element::Water(70)
      , element::Air(80)
      , element::Sky(90)
      , element::Flora(100)
      , element::Fauna(100)
    };
}

SafeShadowStructureAction sideDirectionsElementChanger(Direction::DirectionType direction, int multiplier)
{
    switch (direction)
    {
    case Direction::NorthEast:
        return safeChangeElements({ { element::Ground(multiplier) }
                                  , { element::Sky(multiplier) }
                                  , { element::Water(-multiplier) }
                                  , { element::Air(-multiplier) } });
    case Direction::NorthWest:
        return safeChangeElements({ { element::Ground(multiplier) }
                                  , { element::Sky(-multiplier) }
                                  , { element::Water(-multiplier) }
                                  , { element::Air(multiplier) } });

    case Direction::SouthEast:
        return safeChangeElements({ { element::Ground(-multiplier) }
                                  , { element::Sky(multiplier) }
                                  , { element::Water(multiplier) }
                                  , { element::Air(-multiplier) } });
    case Direction::SouthWest:
        return safeChangeElements({ { element::Ground(-multiplier) }
                                  , { element::Sky(-multiplier) }
                                  , { element::Water(multiplier) }
                                  , { element::Air(multiplier) } });
    default:
        return safeChangeElements({});
    }
    // N.B., empty initialization list - like in Haskell.
    // Presentation tip: show the similarity of C++ and Haskell.
    return safeChangeElements({});
}

ShadowVariator amberPoleVariator(int multiplier)
{
    ShadowVariator variator = [=](const ShadowStructure& structure, Direction::DirectionType direction)
    {
        // N.B.! This can be wrapped into a small 'Changing DSL'.
        // Invent a pairs of dependant elements, for example water-ground, sky-air, amber-chaos.
        // Show it in presentation.
        // N.B.: functions of the element namespace completely fit into this model.
        // Presentation tip: this is a tiny eDSL.

        SafeShadowStructureAction action;
        switch (direction)
        {
        case Direction::North:
            action = safeChangeElements({ {Element::Water,  -multiplier }
                                        , {Element::Ground,  multiplier } });
            break;
        case Direction::South:
            action = safeChangeElements({ element::Water(multiplier)
                                        , element::Ground(multiplier) });
            break;
        case Direction::East:
            action = safeChangeElements({ element::Air(-multiplier)
                                        , element::Sky(multiplier) });
            break;
        case Direction::West:
            action = safeChangeElements({ {Element::Air, multiplier }
                                        , {Element::Sky, multiplier } });
            break;
        default:
            action = sideDirectionsElementChanger(direction, multiplier);
        }

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

ShadowVariator trueAmberVariator()
{
    return amberPoleVariator(1);
}

ShadowVariator amberShadowVariator()
{
    return amberPoleVariator(2);
}

ShadowVariator bergmaShadowVariator()
{
    return amberPoleVariator(3);
}

ShadowVariator trueBergmaVariator()
{
    return amberPoleVariator(4);
}

Shadows amberPoleShadows()
{
    return {
        { AmberShadow,  Shadow { amberShadowVariator(),  amberShadowStructure()} }
      , { TrueAmber,    Shadow { trueAmberVariator(),    trueAmberStructure()  } }
      , { BergmaShadow, Shadow { bergmaShadowVariator(), bergmaShadowStructure() } }
      , { TrueBergma,   Shadow { trueBergmaVariator(),   trueBergmaStructure() } }
    };
}

ShadowPaths amberPolePaths()
{
    return {
        { amberShadowStructure(),  WorldPosition{AmberPoleArea, AmberShadow} }
      , { trueAmberStructure(),    WorldPosition{AmberPoleArea, TrueAmber} }
      , { bergmaShadowStructure(), WorldPosition{AmberPoleArea, BergmaShadow} }
      , { trueBergmaStructure(),   WorldPosition{AmberPoleArea, TrueBergma} }
    };
}

Area amberPoleArea()
{
    return Area { amberPoleShadows(), amberPolePaths() };
}

} // namespace amber
