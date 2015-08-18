#ifndef COMBINATORS_H
#define COMBINATORS_H

#include "identity.h"
#include "lenses.h"

#include <functional>

using namespace std;

namespace lenses
{

namespace // anonymous
{

} // namespace anonymous

/*
struct InStruct_ {} inStruct;

template<typename A, typename B, typename C>
struct InStructProxy
{
    Lens<A, B> l;
    Lens<B, C> r;

    InStructProxy(const Lens<A,B>& lhs)
        : l(lhs)
    {
    }
};

template <typename A, typename B, typename C>
InStructProxy<A, B, C>& operator+(const Lens<A, B>& l,
                                  const InStructProxy<A, B, C>& proxy)
{
    proxy.l = l;
    return proxy;
}

template <typename A, typename B, typename C> InStructProxy<A, B, C>&
    operator+(const InStructProxy<A,B,C>& proxy,
              const Lens<B, C>& r)
{
    proxy.r = r;
    return proxy;
}
*/

class ToProxy
{
public:
    template<typename T>
    T operator () (T a) const { return a; }
} toProxy;

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

    LensStack<A, B, C> operator()()
    {
        return this->get();
    }


    LensStack<A, B, C> get() const
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





#define to < toProxy >


} // namespace lenses

#endif // COMBINATORS_H
