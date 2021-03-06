#include "taskmechanics.h"

namespace amber
{

Artifact pure(const Amber& amber)
{
    return { amber, true, {} };
}

Amber extract(const Artifact& artifact)
{
    return artifact.amber;
}

Artifact eval(const AmberTask& task, const Artifact& artifact)
{
    Artifact newArtifact = artifact;
    try
    {
        Amber newAmber = task(artifact.amber);
        newArtifact.amber = newAmber;
        newArtifact.success = true;
    }
    catch (const std::exception& e)
    {
        newArtifact.systemLog.push_back(e.what());
        newArtifact.success = false;
    }
    return newArtifact;
}

Artifact anyway(const AmberTask& task, const Artifact& artifact)
{
    // do not check artifact's result. Just do task.
    return eval(task, artifact);
}

// Do task when previous result is fail.
Artifact onFail(const AmberTask& task, const Artifact& artifact)
{
    if (!artifact.success)
    {
        Artifact newArtifact = artifact;
        newArtifact.success = true;
        return eval(task, newArtifact);
    }
    return artifact;
}

Artifact times(uint n, const amber::AmberTask& task, const Artifact& artifact)
{
    Artifact newArtifact = artifact;
    for (uint i = 0; i < n; ++i) {
        newArtifact = anyway (task, newArtifact);
    }
    return newArtifact;
}

} // namespace amber

