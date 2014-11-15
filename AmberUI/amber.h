#ifndef AMBER_H
#define AMBER_H

#include "common.h"

namespace amber
{

namespace Pole
{
enum PoleType
{
    PoleAmber,
    PoleChaos
};
}

namespace Element
{
enum ElementType
{
    Air,
    Sky,
    Water,
    Ground
};
}

typedef std::map<Element::ElementType, int> ShadowStructure;
typedef std::function<ShadowStructure(ShadowStructure, Pole::PoleType)> ShadowChanger;

typedef std::map<ShadowStructure, ShadowChanger> AmberStructure;
typedef std::map<ShadowStructure, std::string> KnownShadows;

struct Amber
{
    int hoursElapsed;

    AmberStructure amberStructure;
    KnownShadows shadows;

    // This is an obsolete part.
    Pole::PoleType direction;
    int worldPolePosition;

};

typedef std::function<Amber (const Amber&)> AmberTask;

void changeAmber(const AmberTask& task, Amber& amber);

}

#endif // AMBER_H
