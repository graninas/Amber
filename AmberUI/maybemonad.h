#ifndef MAYBEMONAD_H
#define MAYBEMONAD_H

#include "monadicvalue.h"

namespace monad
{
namespace maybe
{

enum MaybeValue
{
    Just,
    Nothing
};

// Presentation tip:
// Maybe doesn't holding a data when it is Nothing.
template <typename Data> struct Maybe
{
    Data data;
    MaybeValue mValue;
};

template <typename Input> bool isNothing(const MonadicValue<Maybe<Input>>& input)
{
    return input.genericData.mValue == Nothing;
}

template <typename Input> bool isJust(const MonadicValue<Maybe<Input>>& input)
{
    return !isNothing(input);
}

template <typename Input> MonadicValue<Maybe<Input>> wrap(const Input& input)
{
    Maybe<Input> mbValue;
    mbValue.data = input;
    mbValue.mValue = Just;

    MonadicValue<Maybe<Input>> value;
    value.genericData = mbValue;
    return value;
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

template <typename Data> Data maybe(const MonadicValue<Maybe<Data>>& mbValue, const Data& def)
{
    if (isJust(mbValue))
        return mbValue.genericData.data;
    return def;
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

template <typename Input1, typename Input2> MonadicValue<Maybe<std::pair<Input1, Input2>>>
    both(const MonadicValue<Maybe<Input1>>& input1,
         const MonadicValue<Maybe<Input2>>& input2)
{
    if (isNothing(input1) || isNothing(input2))
        return nothing<std::pair<Input1, Input2>>();

    return just(std::pair<Input1, Input2>(input1.genericData.data, input2.genericData.data));
}

namespace unsafe
{
// Presentation tip: unsafe function.
template <typename Data> Data unwrap(const MonadicValue<Maybe<Data>>& input)
{
    if (isNothing(input))
        throw std::logic_error("This is Nothing value, and cannot be unwrapped.");
    return input.genericData.data;
}
} // namespace unsafe

} // namespace maybe
} // namespace monad


#endif // MAYBEMONAD_H
