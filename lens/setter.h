#ifndef SETTER_H
#define SETTER_H

#include <functional>

namespace lenses
{

#define SETTER(A, B, b) [](const A& a, const B& replacer) { A newA = a; newA.b = replacer; return newA; }

#define modify(Type, expr) std::function<Type(Type)>([](Type _value) { return (expr); })

template<typename Type> std::function<Type(Type)> set(Type val)
{
    return [=] (Type) { return val; };
}

} // namespace lenses

#endif // SETTER_H
