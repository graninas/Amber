#ifndef AMBER_H
#define AMBER_H

#include "common.h"

namespace amber
{

struct Amber
{
    int hoursElapsed;
};

typedef std::function<Amber (const Amber&)> AmberTask;

void changeAmber(const AmberTask& task, Amber& amber);

}

#endif // AMBER_H
