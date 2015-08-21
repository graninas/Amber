#ifndef TO_COMBINATOR_H
#define TO_COMBINATOR_H

#include "identity.h"
#include "lens_stack.h"
#include "lenses.h"

#include <functional>

using namespace std;

namespace lenses
{

namespace // anonymous
{

struct ToProxy
{
public:
    template<typename T>
    T operator () (T a) const { return a; }
} toProxy;

/*
template<typename A, typename B>
struct ToLProxy
{
    Lens<A, B> l;

    ToLProxy(const Lens<A,B>& lhs)
        : l(lhs)
    {
    }
};

template<typename A, typename B, typename C>
struct ToRProxy
{
    ToLProxy<A, B> l;
    Lens<B, C> r;

    ToRProxy(const ToLProxy<A, B>& lProxy, const Lens<B, C>& rhs)
        : l(lProxy)
        , r(rhs)
    {
    }

    LS<A, B, C> operator()()
    {
        return this->get();
    }


    LS<A, B, C> get() const
    {
        return zoom(l.l, r);
    }
};

template <typename A, typename B>
ToLProxy<A, B> operator<(const Lens<A, B>& l,
                         const ToProxy&)
{
    return ToLProxy<A, B>(l);
}

template <typename A, typename B, typename C>
ToRProxy<A, B, C> operator>(const ToLProxy<A, B>& proxy,
                            const Lens<B, C>& r)
{
    return ToRProxy<A, B, C>(proxy, r);
}

template <typename A, typename B>
ToLProxy<A, B> mkLProxy(const Lens<A, B>& l)
{
    return ToLProxy<A, B>(l);
}
*/

template <typename L>
LS<L> operator<(const L& l,
                const ToProxy&)
{
    return LS<L>(l);
}

template <typename ST, typename L>
typename ST::template reroll_type<L> operator>(const ST& st, const L& l)
{
    return st.reroll(l);
}


} // namespace anonymous

//#define to < toProxy >


} // namespace lenses

#endif // TO_COMBINATOR_H
