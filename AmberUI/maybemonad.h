#ifndef MAYBEMONAD_H
#define MAYBEMONAD_H

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

template <typename Input> bool isNothing(const Maybe<Input>& input)
{
    return input.mValue == Nothing;
}

template <typename Input> bool isJust(const Maybe<Input>& input)
{
    return !isNothing(input);
}

template <typename Input> Maybe<Input> wrap(const Input& input)
{
    Maybe<Input> mbValue;
    mbValue.data = input;
    mbValue.mValue = Just;
    return mbValue;
}

template <typename Output> Maybe<Output> nothing()
{
    Maybe<Output> mbValue;
    mbValue.mValue = Nothing;
    return mbValue;
}

template <typename Input> Maybe<Input> just(const Input& input)
{
    return wrap(input);
}

template <typename Data> Data maybe(const Maybe<Data>& mbValue, const Data& def)
{
    if (isJust(mbValue))
        return mbValue.data;
    return def;
}

template <typename Input, typename Output> Maybe<Output>
    bind(const Maybe<Input>& input,
         const std::function<Maybe<Output>(Input)>& action)
{
    if (isNothing(input))
    {
        return nothing<Output>();
    }

    return action(input.data);
}

template <typename Input1, typename Input2> Maybe<std::pair<Input1, Input2>>
    both(const Maybe<Input1>& input1,
         const Maybe<Input2>& input2)
{
    if (isNothing(input1) || isNothing(input2))
        return nothing<std::pair<Input1, Input2>>();

    return just(std::pair<Input1, Input2>(input1.data, input2.data));
}

namespace unsafe
{
// Presentation tip: unsafe function.
template <typename Data> Data unwrap(const Maybe<Data>& input)
{
    if (isNothing(input))
        throw std::logic_error("This is Nothing value, and cannot be unwrapped.");
    return input.data;
}
} // namespace unsafe

} // namespace maybe
} // namespace monad


#endif // MAYBEMONAD_H
