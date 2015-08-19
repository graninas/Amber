#ifndef LENSES_H
#define LENSES_H

#include "identity.h"

#include <functional>

namespace lenses
{

template <typename Zoomed1, typename Zoomed2>
struct Lens
{
    std::function<Zoomed2(Zoomed1)> getter;
    std::function<Zoomed1(Zoomed1&, Zoomed2)> setter;
};

template <typename Zoomed1, typename Zoomed2, typename Zoomed3 = Identity, typename Zoomed4 = Identity>
struct LensStack
{
    Lens<Zoomed1, Zoomed2> lens1;
    Lens<Zoomed2, Zoomed3> lens2;
    Lens<Zoomed3, Zoomed4> lens3;
};

template <typename Focused>
Lens<Focused, Identity> idL()
{
    Lens<Focused, Identity> l;
    return l;
}

template <typename Zoomed1, typename Zoomed2>
Lens<Zoomed1, Zoomed2>
    lens(const std::function<Zoomed2(Zoomed1)>& getter,
         const std::function<Zoomed1(Zoomed1, Zoomed2)>& setter)
{
    Lens<Zoomed1, Zoomed2> l;
    l.getter = getter;
    l.setter = setter;
    return l;
}

template <typename Zoomed1, typename Zoomed2, typename Zoomed3, typename Zoomed4>
LensStack<Zoomed1, Zoomed2, Zoomed3, Zoomed4>
    zoom(Lens<Zoomed1, Zoomed2> l1
       , Lens<Zoomed2, Zoomed3> l2
       , Lens<Zoomed3, Zoomed4> l3)
{
    LensStack<Zoomed1, Zoomed2,  Zoomed3, Zoomed4> ls;
    ls.lens1 = l1;
    ls.lens2 = l2;
    ls.lens3 = l3;
    return ls;
}

template <typename Zoomed1, typename Zoomed2, typename Zoomed3>
LensStack<Zoomed1, Zoomed2, Zoomed3, Identity>
    zoom(Lens<Zoomed1, Zoomed2> l1
       , Lens<Zoomed2, Zoomed3> l2)
{
    LensStack<Zoomed1, Zoomed2,  Zoomed3, Identity> ls;
    ls.lens1 = l1;
    ls.lens2 = l2;
    ls.lens3 = idL<Zoomed3>();
    return ls;
}

template <typename Zoomed1, typename Zoomed2>
LensStack<Zoomed1, Zoomed2, Identity, Identity>
    zoom(Lens<Zoomed1, Zoomed2> l1)
{
    LensStack<Zoomed1, Zoomed2, Identity, Identity> ls;
    ls.lens1 = l1;
    ls.lens2 = idL<Zoomed2>();
    ls.lens3 = idL<Identity>();
    return ls;
}

template <typename Zoomed1, typename Zoomed2> bool isFocus(const Lens<Zoomed1, Zoomed2>& l)
{
    return false;
}

template <typename Zoomed1> bool isFocus(const Lens<Zoomed1, Identity>& l)
{
    return true;
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








} // namespace lenses

#endif // LENSES_H
