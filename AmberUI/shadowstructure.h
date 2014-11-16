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
    West
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

typedef std::map<ShadowStructure, WorldPosition> ShadowPaths;

struct Shadow
{
    ShadowVariator variator;
    ShadowStructure structure;
};

typedef std::map<ShadowName, Shadow> Shadows;

struct Area
{
    Shadows shadows;
    ShadowPaths paths;
};

typedef std::map<AreaName, Area> Areas;

void safeStructureChange(ShadowStructure& structure, Element::ElementType elem, int diff);

namespace element
{
ShadowStructure::value_type AmberDistance(int distance);
ShadowStructure::value_type ChaosDistance(int distance);
ShadowStructure::value_type Air(int air);
ShadowStructure::value_type Sky(int sky);
ShadowStructure::value_type Ground(int ground);
ShadowStructure::value_type Water(int water);
ShadowStructure::value_type Flora(int flora);
ShadowStructure::value_type Fauna(int fauna);

}
}

#endif // SHADOWSTRUCTURE_H
