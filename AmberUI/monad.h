#ifndef MONAD_H
#define MONAD_H

#include "common.h"

namespace monad
{

// Generic - a true monad.

template <typename M, typename Input> struct GenericValue
{
    Input input;
    M genericData;
};

template <typename M, typename Input> GenericValue<M, Input> genericWrap(const Input& data)
{
    return wrap(data);
}

template <typename M, typename Input, typename Output> GenericValue<M, Output>
    genericBind(const GenericValue<M, Input>& value,
                const std::function<GenericValue<M, Output>(Input)>& action)
{
    return bind(action, value);
}

namespace maybe
{

enum MaybeValue
{
    Just,
    Nothing
};

struct Maybe
{
    MaybeValue mValue;
};

template <typename Input> GenericValue<Maybe, Input> wrap(const Input& input)
{
    GenericValue<Maybe, Input> value;
    value.genericData = Maybe { Just };
    value.input = input;
    return value;
}

template <typename M = Maybe, typename Input, typename Output> GenericValue<Maybe, Output>
    bind(const GenericValue<Maybe, Input>& input,
         const std::function<GenericValue<Maybe, Output>(Input)>& action)
{
    if (input.genericData.mValue == Nothing)
    {
        GenericValue<Maybe, Output> out;
        out.genericData = Maybe { Nothing };
    }

    return action(input.genericData.data);
}

typedef GenericValue<Maybe, bool> MaybeBool;

} // namespace maybe
} // namespace monad


#endif // MONAD_H
