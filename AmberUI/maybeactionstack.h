#ifndef MAYBEACTIONSTACK_H
#define MAYBEACTIONSTACK_H

#include "maybemonad.h"
#include <functional>

namespace monad
{
namespace maybe
{

// Experimental Maybe stack.
// There are a better solutions using Variadic templates or tuples.

template <typename M1,
          typename M2,
          typename M3 = Identity,
          typename M4 = Identity,
          typename M5 = Identity,
          typename M6 = Identity>
struct MaybeActionStack
{
    std::function<Maybe<M2>(M1)> action1;
    std::function<Maybe<M3>(M2)> action2;
    std::function<Maybe<M4>(M3)> action3;
    std::function<Maybe<M5>(M4)> action4;
    std::function<Maybe<M6>(M5)> action5;
};

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6>
Maybe<M6> evalMaybes(const Maybe<M1>& m1, const MaybeActionStack<M1, M2, M3, M4, M5, M6>& stack)
{
    Maybe<M2> m2 = bind<M1, M2>(m1, stack.action1);
    Maybe<M3> m3 = bind<M2, M3>(m2, stack.action2);
    Maybe<M4> m4 = bind<M3, M4>(m3, stack.action3);
    Maybe<M5> m5 = bind<M4, M5>(m4, stack.action4);
    Maybe<M6> m6 = bind<M5, M6>(m5, stack.action5);
    return m6;
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
Maybe<M5> evalMaybes(const Maybe<M1>& m1, const MaybeActionStack<M1, M2, M3, M4, M5, Identity>& stack)
{
    Maybe<M2> m2 = bind<M1, M2>(m1, stack.action1);
    Maybe<M3> m3 = bind<M2, M3>(m2, stack.action2);
    Maybe<M4> m4 = bind<M3, M4>(m3, stack.action3);
    Maybe<M5> m5 = bind<M4, M5>(m4, stack.action4);
    return m5;
}

/*
template <typename Input, typename Output> Maybe<Output>
    bind(const Maybe<Input>& input,
         const std::function<Maybe<Output>(Input)>& action)
*/
template <typename M1, typename M2, typename M3, typename M4>
Maybe<M4> evalMaybes(const Maybe<M1>& m1, const MaybeActionStack<M1, M2, M3, M4, Identity, Identity>& stack)
{
    Maybe<M2> m2 = bind<M1, M2>(m1, stack.action1);
    Maybe<M3> m3 = bind<M2, M3>(m2, stack.action2);
    Maybe<M4> m4 = bind<M3, M4>(m3, stack.action3);
    return m4;
}

template <typename M1, typename M2, typename M3>
Maybe<M3> evalMaybes(const Maybe<M1>& m1, const MaybeActionStack<M1, M2, M3, Identity, Identity, Identity>& stack)
{
    Maybe<M2> m2 = bind<M1, M2>(m1, stack.action1);
    Maybe<M3> m3 = bind<M2, M3>(m2, stack.action2);
    return m3;
}

template <typename M1, typename M2, typename M3>
Maybe<M2> evalMaybes(const Maybe<M1>& m1, const MaybeActionStack<M1, M2, Identity, Identity, Identity, Identity>& stack)
{
    Maybe<M2> m2 = bind<M1, M2>(m1, stack.action1);
    return m2;
}

template <typename M1> std::function<Maybe<Identity>(M1)> idA()
{
    return [](const M1&)
    {
        return just(Identity {});
    };
}


template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6>
MaybeActionStack<M1, M2, M3, M4, M5, M6>
    bindMany(const std::function<Maybe<M2>(M1)> action1,
             const std::function<Maybe<M3>(M2)> action2,
             const std::function<Maybe<M4>(M3)> action3,
             const std::function<Maybe<M5>(M4)> action4,
             const std::function<Maybe<M6>(M5)> action5)
{
    MaybeActionStack<M1, M2, M3, M4, M5, M6> stack;
    stack.action1 = action1;
    stack.action2 = action2;
    stack.action3 = action3;
    stack.action4 = action4;
    stack.action5 = action5;
    return stack;
}

template <typename M1, typename M2, typename M3, typename M4, typename M5>
MaybeActionStack<M1, M2, M3, M4, M5, Identity>
    bindMany(const std::function<Maybe<M2>(M1)> action1,
             const std::function<Maybe<M3>(M2)> action2,
             const std::function<Maybe<M4>(M3)> action3,
             const std::function<Maybe<M5>(M4)> action4)
{
    MaybeActionStack<M1, M2, M3, M4, M5, Identity> stack;
    stack.action1 = action1;
    stack.action2 = action2;
    stack.action3 = action3;
    stack.action4 = action4;
    stack.action5 = idA<M5>();
    return stack;
}

template <typename M1, typename M2, typename M3, typename M4>
MaybeActionStack<M1, M2, M3, M4, Identity, Identity>
    bindMany(const std::function<Maybe<M2>(M1)> action1,
             const std::function<Maybe<M3>(M2)> action2,
             const std::function<Maybe<M4>(M3)> action3)
{
    MaybeActionStack<M1, M2, M3, M4, Identity, Identity> stack;
    stack.action1 = action1;
    stack.action2 = action2;
    stack.action3 = action3;
    stack.action4 = idA<M4>();
    stack.action5 = idA<Identity>();
    return stack;
}

template <typename M1, typename M2, typename M3>
MaybeActionStack<M1, M2, M3, Identity, Identity, Identity>
    bindMany(const std::function<Maybe<M2>(M1)> action1,
             const std::function<Maybe<M3>(M2)> action2)
{
    MaybeActionStack<M1, M2, M3, Identity, Identity, Identity> stack;
    stack.action1 = action1;
    stack.action2 = action2;
    stack.action3 = idA<M3>();
    stack.action4 = idA<Identity>();
    stack.action5 = idA<Identity>();
    return stack;
}

} // namespace maybe
} // namespace monad


#endif // MAYBEACTIONSTACK_H
