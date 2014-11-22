#ifndef MAYBEMONAD_H
#define MAYBEMONAD_H

#include "monadicvalue.h"

namespace monad
{

enum MaybeValue
{
    Just,
    Nothing
};

template <typename Data> struct Maybe
{
    Data data;
    MaybeValue mValue;
};

template <typename Input> MonadicValue<Maybe<Input>> wrap(const Input& input)
{
    Maybe<Input> mbValue;
    mbValue.data = input;
    mbValue.mValue = Just;

    MonadicValue<Maybe<Input>> value;
    value.genericData = mbValue;
    return value;
}

template <typename Input> bool isNothing(const MonadicValue<Maybe<Input>>& input)
{
    return input.genericData.mValue == Nothing;
}

template <typename Output> MonadicValue<Maybe<Output>> nothing()
{
    Maybe<Output> mbValue;
    mbValue.mValue = Nothing;

    MonadicValue<Maybe<Output>> value;
    value.genericData = mbValue;
    return value;
}

template <typename Input> MonadicValue<Maybe<Input>> just(const Input& input)
{
    return wrap(input);
}

template <typename Input, typename Output> MonadicValue<Maybe<Output>>
    bind(const MonadicValue<Maybe<Input>>& input,
         const std::function<MonadicValue<Maybe<Output>>(Input)>& action)
{
    if (isNothing(input))
    {
        return nothing<Output>();
    }

    return action(input.genericData.data);
}

} // namespace monad


#endif // MAYBEMONAD_H
