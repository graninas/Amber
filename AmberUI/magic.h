#ifndef MAGIC_H
#define MAGIC_H

#include "amber.h"

#include "common.h"

namespace magic
{

using namespace amber;

struct Artifact
{
    Artifact(const Amber& a, int r)
    {
        amber = a;
        result = r;
    }

    Amber amber;
    int result;
    std::vector<std::string> systemLog;
};

Artifact wrap(const Amber& amber);
Artifact unwrap(const Amber& amber);
Artifact eval(const AmberTask& task, const Artifact& artifact);
Artifact anyway(const AmberTask& task, const Artifact& artifact);


}

#endif // MAGIC_H
