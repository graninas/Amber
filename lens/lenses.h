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


template <typename... Args>
struct LensStack2;

template<typename Head, typename... Tail>
struct LensStack2<Head, Tail...> : LensStack2<Tail...>
{
    LensStack2(Head h, Tail... tail)
         : LensStack2<Tail...>(tail...), head_(h)
    {}

    typedef LensStack2<Tail...> base_type;
    typedef Head                value_type;

    //base_type& base = static_cast<base_type&>(*this);
    Head       head_;
};

template <>
struct LensStack2<>
{};

/*

template <typename... Tail>
struct LensStack3 {};


template<typename H1, typename... Tail>
struct LensStack3<H1, Tail...>
{
};


template<typename H1, typename H2, typename... Tail>
struct LensStack3<H1, H2, Tail...>
    : LensStack3<H2, Tail...>
{
    LensStack3(Lens<H1, H2> l, Tail... tail)
        : LensStack3<H2, Tail...>(tail...)
        , m_lens(l)
    {}

    Lens<H1, H2> m_lens;
};


template<typename H1, typename H2, typename H3, typename... Tail>
struct LensStack3<H1, H2, H3, Tail...>
    : LensStack3<H2, H3, Tail...>
{
    LensStack3(Lens<H1, H2> l1, Lens<H2, H3> l2, Tail... tail)
        : LensStack3<H2, H3, Tail...>(l2, tail...)
        , m_lens1(l1)
    {}

    Lens<H1, H2> m_lens1;
};

*/


template <typename... Tail>
struct LensStack3 {};

template<typename L1, typename... Tail>
struct LensStack3<L1, Tail...>
    : LensStack3<Tail...>
{
    LensStack3(L1 l1, Tail... tail)
        : LensStack3<Tail...>(tail...)
        , m_lens(l1)
    {}

    L1 m_lens;
};


//////////////////


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









} // namespace lenses

#endif // LENSES_H
