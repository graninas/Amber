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

template <typename Zoomed1,
          typename Zoomed2,
          typename Zoomed3>
Zoomed1 evalLens(const LensStack<Zoomed1, Zoomed2, Zoomed3, Identity>& lensStack,
                 const Zoomed1& zoomed1,
                 const std::function<Zoomed3(Zoomed3)>& variator)
{
    Zoomed1 z1 = zoomed1;
    Zoomed2 z2 = lensStack.lens1.getter(z1);
    Zoomed3 z3 = lensStack.lens2.getter(z2);
    z2 = lensStack.lens2.setter(z2, variator(z3));
    z1 = lensStack.lens1.setter(z1, z2);
    return z1;
}

template <typename Zoomed1,
          typename Zoomed2>
Zoomed1 evalLens(const LensStack<Zoomed1, Zoomed2, Identity, Identity>& lensStack,
                 const Zoomed1& zoomed1,
                 const std::function<Zoomed2(Zoomed2)>& variator)
{
    Zoomed1 z1 = zoomed1;
    Zoomed2 z2 = lensStack.lens1.getter(z1);
    return lensStack.lens1.setter(z1, variator(z2));
}



template <typename Zoomed1,
          typename Zoomed2,
          typename Zoomed3>
Zoomed1 over(const LensStack<Zoomed1, Zoomed2, Zoomed3, Identity>& lensStack,
             const Zoomed1& zoomed1,
             const std::function<Zoomed3(Zoomed3)>& variator)
{
    return evalLens(lensStack, zoomed1, variator);
}

template <typename Zoomed1,
          typename Zoomed2>
Zoomed1 over(const LensStack<Zoomed1, Zoomed2, Identity, Identity>& lensStack,
             const Zoomed1& zoomed1,
             const std::function<Zoomed2(Zoomed2)>& variator)
{
    return evalLens(lensStack, zoomed1, variator);
}



template <typename Zoomed1,
          typename Zoomed2,
          typename Zoomed3>
Zoomed1 set(const LensStack<Zoomed1, Zoomed2, Zoomed3, Identity>& lensStack,
             const Zoomed1& zoomed1,
             const Zoomed3& value)
{
    return evalLens(lensStack, zoomed1, set(value));
}

template <typename Zoomed1,
          typename Zoomed2>
Zoomed1 set(const LensStack<Zoomed1, Zoomed2, Identity, Identity>& lensStack,
             const Zoomed1& zoomed1,
             const Zoomed2& value)
{
    return evalLens(lensStack, zoomed1, set(value));
}


} // namespace lenses

#endif // SETTER_H
