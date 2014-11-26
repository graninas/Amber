#include "magic.h"

namespace magic
{

using namespace amber;

Artifact wrap(const Amber& amber)
{
    Artifact artifact { amber, true, {} };
    return artifact;
}

Amber unwrap(const Artifact& artifact)
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
        qDebug() << "task success.";
    }
    catch (const std::exception& e)
    {
        newArtifact.systemLog.push_back(e.what());
        newArtifact.success = false;
        qDebug() << "task fail.";
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

}
