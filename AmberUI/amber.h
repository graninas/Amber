#ifndef AMBER_H
#define AMBER_H

#include "common.h"
#include "shadowstructure.h"

namespace amber
{

typedef std::map<ShadowStructure, ShadowVariator> AmberStructure;
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
