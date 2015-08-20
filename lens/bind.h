#ifndef TYPE_HELPER_H
#define TYPE_HELPER_H

#include "lenses.h"

namespace lenses
{

template <typename H1, typename H2>
LensStack3<Lens<H1, H2>>
    bind(const Lens<H1, H2>& l1)
{
    return LensStack3<Lens<H1, H2>>(l1);
}

template <typename H1, typename H2, typename H3>
LensStack3<Lens<H1, H2>, Lens<H2, H3>>
    bind(const Lens<H1, H2>& l1, const Lens<H2, H3>& l2)
{
    return LensStack3<Lens<H1, H2>, Lens<H2, H3>>(l1, l2);
}

template <typename H1, typename H2, typename H3, typename H4>
LensStack3<Lens<H1, H2>, Lens<H2, H3>, Lens<H3, H4>>
    bind(const Lens<H1, H2>& l1, const Lens<H2, H3>& l2, const Lens<H3, H4>& l3)
{
    return LensStack3<Lens<H1, H2>, Lens<H2, H3>, Lens<H3, H4>>(l1, l2, l3);
}

template <typename H1, typename H2, typename H3, typename H4, typename H5>
LensStack3<Lens<H1, H2>, Lens<H2, H3>, Lens<H3, H4>, Lens<H4, H5>>
    bind(const Lens<H1, H2>& l1, const Lens<H2, H3>& l2, const Lens<H3, H4>& l3, const Lens<H4, H5>& l4)
{
    return LensStack3<Lens<H1, H2>, Lens<H2, H3>, Lens<H3, H4>, Lens<H4, H5>>(l1, l2, l3, l4);
}

} // namespace lenses

#endif // TYPE_HELPER_H
