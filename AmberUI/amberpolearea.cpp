#include "amberpolearea.h"

#include "common.h"
#include "shadowmechanics.h"
#include "knownareas.h"

namespace amber
{

ShadowStructure amberShadowStructure()
{
    return {
        element::AmberDistance(1)
      , element::ChaosDistance(99)
      , element::Air(50)
      , element::Ground(50)
      , element::Sky(100)
      , element::Water(30)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowStructure trueAmberStructure()
{
    return {
        element::AmberDistance(0)
      , element::ChaosDistance(100)
      , element::Air(60)
      , element::Ground(80)
      , element::Sky(80)
      , element::Water(20)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowStructure bergmaShadowStructure()
{
    return {
        element::AmberDistance(2)
      , element::ChaosDistance(98)
      , element::Air(60)
      , element::Ground(80)
      , element::Sky(90)
      , element::Water(20)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowStructure trueBergmaStructure()
{
    return {
        element::AmberDistance(2)
      , element::ChaosDistance(98)
      , element::Air(70)
      , element::Ground(90)
      , element::Sky(100)
      , element::Water(10)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowVariator amberVariator()
{
    ShadowVariator variator = [](const ShadowStructure& structure, Direction::DirectionType direction)
    {
        int waterGroundNSChange = 2;
        int waterGroundWEChange = 1;


        // N.B.! This can be wrapped into a small 'Changing DSL'.
        // Invent a pairs of dependant elements, for example water-ground, sky-air, amber-chaos.
        // Show it in presentation.
        /*
        switch (direction)
        {
        case Direction::North:


            safeStructureChange(newStructure, Element::Water,         -waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundNSChange);
            break;
        case Direction::South:
            safeStructureChange(newStructure, Element::Water,          waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundNSChange);
            break;
        case Direction::East:
            safeStructureChange(newStructure, Element::Water,         -waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundWEChange);
            break;
        case Direction::West:
            safeStructureChange(newStructure, Element::Water,          waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundWEChange);
            break;
        };

        magic::Result<ShadowStructue> result = magic::runSafe(changeAction, structure);
        if (magic::isSuccess(result))
            return magic::resultData(result);
        else // TODO - fail tolerance, error reporting
            return structure;
        */

        return structure;
    };
    return variator;
}

ShadowVariator bergmaVariator()
{
    ShadowVariator variator = [](const ShadowStructure& structure, Direction::DirectionType direction)
    {
        int waterGroundNSChange = 1;
        int airChange = 2;
        int waterGroundWEChange = 1;
        int amberChaosDistanceChange = 1;

        // N.B.! This can be wrapped into a small 'Changing DSL'.
        // Invent a pairs of dependant elements, for example water-ground, sky-air, amber-chaos.
        // Show it in presentation.
        /*
        ShadowStructure newStructure = structure;
        switch (direction)
        {
        case Direction::North:
            safeStructureChange(newStructure, Element::Water,         -waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundNSChange);
            safeStructureChange(newStructure, Element::Air,            airChange);
            safeStructureChange(newStructure, Element::AmberDistance,  amberChaosDistanceChange);
        case Direction::South:
            safeStructureChange(newStructure, Element::Water,          waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundNSChange);
            safeStructureChange(newStructure, Element::Air,           -airChange);
            safeStructureChange(newStructure, Element::ChaosDistance, -amberChaosDistanceChange);
        case Direction::East:
            safeStructureChange(newStructure, Element::Water,         -waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundWEChange);
            safeStructureChange(newStructure, Element::Air,            airChange);
            safeStructureChange(newStructure, Element::AmberDistance,  amberChaosDistanceChange);
        case Direction::West:
            safeStructureChange(newStructure, Element::Water,          waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundWEChange);
            safeStructureChange(newStructure, Element::Air,           -airChange);
            safeStructureChange(newStructure, Element::ChaosDistance, -amberChaosDistanceChange);
        };
        */

        return structure;
    };
    return variator;
}

Shadows amberPoleShadows()
{
    return {
        { AmberShadow,  Shadow { amberVariator(),  amberShadowStructure()} }
      , { TrueAmber,    Shadow { amberVariator(),  trueAmberStructure()  } }
      , { BergmaShadow, Shadow { bergmaVariator(), bergmaShadowStructure() } }
      , { TrueBergma,   Shadow { bergmaVariator(), trueBergmaStructure() } }
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
