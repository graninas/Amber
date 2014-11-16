#include "magic.h"

namespace magic
{

Artifact wrap(const Amber& amber)
{
    Artifact artifact { amber, 0 };
    return artifact;
}

Amber unwrap(const Artifact& artifact)
{
    return artifact.amber;
}

Artifact eval(const AmberTask& task, const Artifact& artifact)
{
    // This is not safe code.
    return Artifact(task(artifact.amber), artifact.result);
}

Artifact anyway(const AmberTask& task, const Artifact& artifact)
{
    // do not check artifact's result. Just do task.
    return eval(task, artifact);
}

}
