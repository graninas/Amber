#ifndef AUTOLENS_H
#define AUTOLENS_H

#include "lenses.h"

#include <functional>

namespace lenses
{

#define GETTER(A, b)    [](const A& a)                    { return a.b; }
#define SETTER(A, B, b) [](const A& a, const B& replacer) { A newA = a; newA.b = replacer; return newA; }


#define MK_LENS(A, B, member) Lens<A, B> member##L() { \
    return lens<A, B> ( GETTER(A, member) \
                      , SETTER(A, B, member)); }

#define modify(Type, expr) std::function<Type(Type)>([](Type _value) { return (expr); })

template<typename Type> std::function<Type(Type)> set(Type val)
{
    return [=] (Type) { return val; };
}

} // namespace lenses


#endif // AUTOLENS_H
