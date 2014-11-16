#include "magic.h"

namespace magic
{

template <class D> Result<D> successResult(const D& data)
{
    return Result { data, ResultValue::Success };
}

template <class D> Result<D> failResult(const D& data)
{
    return Result { data, ResultValue::Fail };
}

template <class D> bool isSuccess(const Result<D>& result)
{
    return result.result == ResultValue::Success;
}

template <class D> bool isFail(const Result<D>& result)
{
    return result.result == ResultValue::Fail;
}

template <class D> D resultData(const Result<D>& result)
{
    return result.data;
}


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
