#ifndef MAGIC_H
#define MAGIC_H

#include "amber.h"

namespace amber
{

namespace Result
{
    enum ResultType
    {
        Success,
        Fail
    };
}

template <class D> struct Value
{
    D data;
    Result::ResultType result;
};

template <class D> Value<D> success(const D& data)
{
    return {data, Result::Success};
}

template <class D> Value<D> fail(const D& data)
{
    return {data, Result::Fail};
}

template <class D> bool isSuccess(const Value<D>& value)
{
    return value.result == Result::Success;
}

template <class D> bool isFail(const Value<D>& value)
{
    return value.result == Result::Fail;
}

template <class D> D valueData(const Value<D>& value)
{
    return value.data;
}

struct Artifact
{
    Amber amber;
    bool success;
    std::vector<std::string> systemLog;
};

Artifact pure(const Amber& amber);
Amber extract(const Artifact& amber);
Artifact eval(const AmberTask& task, const Artifact& artifact);
Artifact anyway(const AmberTask& task, const Artifact& artifact);
Artifact onFail(const AmberTask& task, const Artifact& artifact);
Artifact times(uint n, const AmberTask& task, const Artifact& artifact);

} // namespace amber

#endif // MAGIC_H
