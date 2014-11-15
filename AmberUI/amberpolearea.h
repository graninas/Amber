#ifndef AMBERSHADOW_H
#define AMBERSHADOW_H

#include "amber.h"
#include "common.h"

#include "knownshadows.h"
#include "knownareas.h"

namespace amber
{

ShadowVariator amberVariator()
{
    ShadowVariator variator = [](const ShadowStructure& structure, Direction::DirectionType direction)
    {
        int waterGroundNSChange = 2;
        int waterGroundWEChange = 1;

        // N.B.! This can be wrapped into a small 'Changing DSL'.
        // Invent a pairs of dependant elements, for example water-ground, sky-air, amber-chaos.
        // Show it in presentation.
        ShadowStructure newStructure = structure;
        switch (direction)
        {
        case Direction::North:
            safeStructureChange(newStructure, Element::Water,         -waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundNSChange);
        case Direction::South:
            safeStructureChange(newStructure, Element::Water,          waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundNSChange);
        case Direction::East:
            safeStructureChange(newStructure, Element::Water,         -waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundWEChange);
        case Direction::West:
            safeStructureChange(newStructure, Element::Water,          waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundWEChange);
        };

        return newStructure;
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

        return newStructure;
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
        { amberShadowStructure(),  ShadowPath{AmberPoleArea, AmberShadow} }
      , { trueAmberStructure(),    ShadowPath{AmberPoleArea, TrueAmber} }
      , { bergmaShadowStructure(), ShadowPath{AmberPoleArea, BergmaShadow} }
      , { trueBergmaStructure(),   ShadowPath{AmberPoleArea, TrueBergma} }
    };
}

Area amberPoleArea()
{
    return Area { amberPoleShadows(), amberPolePaths() };
}

} // namespace amber

#endif // AMBERSHADOW_H
