#ifndef LENS_STACK_H
#define LENS_STACK_H

#include <functional>

namespace lenses
{

template <typename... Tail>
struct LS
{
    template <typename Focus>
        Focus apply(const Focus& val, const std::function<Focus(Focus)>& variator) const
    {
        return variator(val);
    }

    template <typename Reroll, typename Lx>
    void reroll_(Reroll& rerolled, const Lx& lx)
    {
        rerolled.m_lens = lx;
    }
};

template<typename L1, typename... Tail>
struct LS<L1, Tail...>
    : LS<Tail...>
{
    typedef LS<Tail...> base_type;
    typedef L1          value_type;

    LS() : LS<Tail...>()
    {}

    LS(L1 l1, Tail... tail)
        : LS<Tail...>(tail...)
        , m_lens(l1)
    {}

    template <typename Lx>
    LS<L1, Tail..., Lx> reroll(const Lx& lx)
    {
        LS<L1, Tail..., Lx> rerolled;
        rerolled.m_lens = m_lens;
        base.reroll_(rerolled.base, lx);
        return rerolled;
    }

    template <typename Reroll, typename Lx>
    void reroll_(Reroll& rerolled, const Lx& lx)
    {
        rerolled.m_lens = m_lens;
        base.reroll_(rerolled.base, lx);
    }

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

    base_type& base = static_cast<base_type&>(*this);
    L1 m_lens;
};

} // namespace lenses

#endif // LENS_STACK_H
