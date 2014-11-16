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

// Presentation tip
// Difficulties with template separated implementation:
// the '.tpp' pattern;
// the 'extern' keyword;
// the std::function templating problem.
// Consider:
// http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
// https://stackoverflow.com/questions/115703/storing-c-template-function-definitions-in-a-cpp-file/15561347#15561347
// http://stackoverflow.com/questions/8130602/using-extern-template-c0x
// http://stackoverflow.com/questions/3575901/can-lambda-functions-be-templated

template <class D> struct Result
{
    D data;
    ResultValue::ResultValueType result;
};

template <class D> Result<D> successResult(const D& data)
{
    // Presentation tip.
    // Can't use initialisaion lists with template struct.
    Result<D> res;
    res.data = data;
    res.result = ResultValue::Success;
    return res;
}

template <class D> Result<D> failResult(const D& data)
{
    // Presentation tip.
    // Can't use initialisaion lists with template struct.
    Result<D> res;
    res.data = data;
    res.result = ResultValue::Fail;
    return res;
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

// Presentation tip
// In order to do a monadic actions connecting for abstract type D,
// a template std::function is needed! Something like this:
// typedef template <class D> std::function<Result<D>(D)> SafeAction;
// SafeAction<ShadowResult> action = [](const D& data) { return safeChangeData(data); }
// Consider http://stackoverflow.com/questions/3575901/can-lambda-functions-be-templated


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
