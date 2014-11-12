#ifndef MAGIC_H
#define MAGIC_H

#include "amber.h"

#include "common.h"

namespace magic
{

using namespace amber;

struct Artifact
{
    Amber amber;
    int result;
};

Artifact wrap(const Amber& amber)
{
    Artifact artifact { amber, 0 };
    return artifact;
}

Artifact eval(const AmberTask& task, const Artifact& artifact)
{
    auto newAmber = task(artifact.amber);
}

Artifact anyway(const AmberTask& task, const Artifact& artifact)
{
    artifactResult = eval(amberTask, artifact);
}


}

#endif // MAGIC_H
