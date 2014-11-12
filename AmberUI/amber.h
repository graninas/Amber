#ifndef AMBER_H
#define AMBER_H

#include "common.h"

namespace amber
{
    typedef std::vector<int> Amber;

    typedef std::function<Amber(const Amber&)> AmberTask;


    Amber changeAmber(const AmberTask& task, const Amber& amber);
}

#endif // AMBER_H
