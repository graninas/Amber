#ifndef SHADOWSTRUCTURE_H
#define SHADOWSTRUCTURE_H

#include "common.h"

namespace amber
{

namespace Pole
{
enum PoleType
{
    Amber,
    Chaos
};
}

namespace Element
{
enum ElementType
{
    ChaosDistance,
    AmberDistance,
    Air,
    Sky,
    Water,
    Ground,
    Flora,
    Fauna
};
}

namespace Direction
{
enum DirectionType
{
    North,
    South,
    East,
    West,
    NorthEast,
    NorthWest,
    SouthEast,
    SouthWest
};
}


typedef std::string ShadowName;
typedef std::string AreaName;

struct WorldPosition
{
    AreaName area;
    ShadowName shadow;
};

typedef std::map<Element::ElementType, int> ShadowStructure;
typedef std::function<ShadowStructure(ShadowStructure, Direction::DirectionType)> ShadowVariator;

typedef double ShadowInfluence;

struct Shadow
{
    ShadowVariator variator;
    ShadowStructure structure;
    ShadowInfluence influence;
};

typedef std::map<ShadowName, Shadow> Shadows;

struct Area
{
    Shadows shadows;
};

typedef std::map<AreaName, Area> Areas;

}

#endif // SHADOWSTRUCTURE_H
