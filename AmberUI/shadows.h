#ifndef SHADOWS_H
#define SHADOWS_H

#include "amber.h"
#include "common.h"

namespace shadows
{

using namespace amber;


const AmberTask goNorth = [](const amber::Amber& amber) -> amber::Amber
{
    return amber;
};

const AmberTask tickDay = [](const amber::Amber& amber) -> amber::Amber
{
    return amber;
};





}

#endif // SHADOWS_H
