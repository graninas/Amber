#ifndef MAGIC_H
#define MAGIC_H

#include "amber.h"
#include "common.h"

namespace magic
{

using namespace amber;

namespace Result
{
enum ResultType
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

template <class D> struct Value
{
    D data;
    Result::ResultType result;
};

template <class D> Value<D> success(const D& data)
{
    // Presentation tip.
    // Can't use initialisaion lists with template struct.
    Value<D> value;
    value.data = data;
    value.result = Result::Success;
    return value;
}

template <class D> Value<D> fail(const D& data)
{
    // Presentation tip.
    // Can't use initialisaion lists with template struct.
    Value<D> value;
    value.data = data;
    value.result = Result::Fail;
    return value;
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
