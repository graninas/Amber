#ifndef MAGIC_H
#define MAGIC_H

#include "amber.h"
#include "common.h"

namespace magic
{

using namespace amber;

namespace ResultValue
{
enum ResultValueType
{
    Success,
    Fail
};
}

template <class D> struct Result
{
    D data;
    ResultValue::ResultValueType result;
};

template <class D> Result<D> successResult(const D& data);
template <class D> Result<D> failResult(const D& data);
template <class D> bool isSuccess(const Result<D>& result);
template <class D> bool isFail(const Result<D>& result);
template <class D> D resultData(const Result<D>& result);


// Presentation tip
// In order to do a monadic actions connecting for abstract type D,
// a template std::function is needed! Something like this:
// typedef template <class D> std::function<Result<D>(D)> SafeAction;
// SafeAction<ShadowResult> action = [](const D& data) { return safeChangeData(data); }



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
Amber unwrap(const Artifact& amber);
Artifact eval(const AmberTask& task, const Artifact& artifact);
Artifact anyway(const AmberTask& task, const Artifact& artifact);


}

#endif // MAGIC_H
