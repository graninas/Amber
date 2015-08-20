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

template <typename... Tail>
struct LS
{

template <typename Focus>
    Focus apply(const Focus& val, const std::function<Focus(Focus)>& variator) const
{
    return variator(val);
}

};

template<typename L1, typename... Tail>
struct LS<L1, Tail...>
    : LS<Tail...>
{
    LS(L1 l1, Tail... tail)
        : LS<Tail...>(tail...)
        , m_lens(l1)
    {}

    L1 get() const
    {
        return m_lens;
    }

    template <typename H1, typename Focus>
        H1 apply(const H1& val, const std::function<Focus(Focus)>& variator) const
    {
        H1 z1 = val;
        auto z2 = m_lens.getter(z1);
        z2 = base.apply(z2, variator);
        z1 = m_lens.setter(z1, z2);
        return z1;
    }

    typedef LS<Tail...> base_type;
    typedef L1          value_type;

    base_type& base = static_cast<base_type&>(*this);

    L1 m_lens;
};

template <typename H1, typename H2, typename H3, typename H4>
H1 evalLensSt(const LS<Lens<H1, H2>, Lens<H2, H3>, Lens<H3, H4>>& ls,
                   const H1& zoomed1,
                   const std::function<H4(H4)>& variator)
{
    return ls.apply(zoomed1, variator);
}


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
