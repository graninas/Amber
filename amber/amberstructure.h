#ifndef AMBERSTRUCTURE_H
#define AMBERSTRUCTURE_H

#include <string>
#include <map>
#include <list>

#include <functional>
#include <algorithm>

namespace amber
{

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

struct NearestPlace
{
    AreaName area;
    ShadowName shadow;
};

typedef std::map<Element::ElementType, int> ShadowStructure;
typedef std::function<ShadowStructure(ShadowStructure, Direction::DirectionType)> ShadowVariator;
typedef double ShadowInfluence;

struct Shadow
{
    ShadowName name;
    ShadowVariator variator;
    ShadowStructure structure;
    ShadowInfluence influence;
};

typedef std::map<ShadowName, Shadow> Shadows;

typedef std::function<ShadowStructure(ShadowStructure, int)> TimedShadowVariator;

struct ShadowStorm
{
    TimedShadowVariator pathVariator;
    ShadowStructure currentShadow;
    ShadowInfluence outerInfluence;
    ShadowInfluence innerInfluence;
    int timeToStart;
    int timeToLive;
};

typedef std::list<ShadowStorm> ShadowStorms;

struct Area
{
    Shadows shadows;
};

typedef std::map<AreaName, Area> Areas;

typedef std::list<std::string> Log;

struct Amber
{
    int hoursElapsed;

    ShadowStorms storms;
    Areas areas;

    NearestPlace nearestPlace;
    ShadowStructure playerShadowStructure;

    Log log;
};

struct Amber2
{
    NearestPlace nearestPlace;
    ShadowStructure playerPos;
};

} // namespace amber

#endif // AMBERSTRUCTURE_H
