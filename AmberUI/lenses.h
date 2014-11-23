#ifndef LENSES_H
#define LENSES_H

// Experimental 'lenses-like' design.

namespace experimental
{


namespace lenses
{

template <typename Input, typename Zoomed, typename... Zoomers> struct Lense
{
    std::function<Zoomed(Input)> zoomer;
    Lense<Input, Zoomers...> lenses;
};

template <typename Input, typename Zoomed, typename... Zoomers> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed, Zoomers...>& l, const Input& input)
{
    std::list<Zoomed> zoomed;
    if (sizeof...(Zoomers) == 0)
    {
        zoomed.push_back(l.zoomer(input));
    }
    else
    {
        std::for_each(l.lenses.begin(), l.lenses.end(),
                      [&zoomed, &input](const Lense<Input, Zoomers...>& internalLense)
        {
            std::list<Zoomed> rolledOut = rolloutLense(internalLense, input);
            zoomed.insert(zoomed.end(), rolledOut.begin(), rolledOut.end());
        });
    }
    return zoomed;
}

template <typename Input, typename Zoomed> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed>& l, const Input& input)
{
    std::list<Zoomed> zoomed { l.zoomer(input) };
    return zoomed;
}


template <typename Input, typename Zoomed, typename... Zoomers>
    std::list<Zoomed>
    overLense(const Lense<Input, Zoomed, Zoomers...>& l,
              const Input& input,
              const std::function<Zoomed(Zoomed)>& action)
{
    std::list<Zoomed> zoomed = rolloutLense(l, input);
    std::transform(zoomed.begin(), zoomed.end(), zoomed.begin(), action);
    return zoomed;
}

/*
template <typename Input, typename Zoomed, typename... Zoomers> struct Lense
{
    std::function<Zoomed(Input)> zoomer;
    Lense<Input, Zoomers...> lenses;
};

template <typename Input, typename Zoomed, typename... Zoomers> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed, Zoomers...>& l, const Input& input)
{
    std::list<Zoomed> zoomed;
    if (sizeof...(Zoomers) == 0)
    {
        zoomed.push_back(l.zoomer(input));
    }
    else
    {
        std::for_each(l.lenses.begin(), l.lenses.end(),
                      [&zoomed, &input](const Lense<Input, Zoomers...>& internalLense)
        {
            std::list<Zoomed> rolledOut = rolloutLense(internalLense, input);
            zoomed.insert(zoomed.end(), rolledOut.begin(), rolledOut.end());
        });
    }
    return zoomed;
}

template <typename Input, typename Zoomed> std::list<Zoomed>
    rolloutLense(const Lense<Input, Zoomed>& l, const Input& input)
{
    std::list<Zoomed> zoomed { l.zoomer(input) };
    return zoomed;
}


template <typename Input, typename Zoomed, typename... Zoomers>
    std::list<Zoomed>
    overLense(const Lense<Input, Zoomed, Zoomers...>& l,
              const Input& input,
              const std::function<Zoomed(Zoomed)>& action)
{
    std::list<Zoomed> zoomed = rolloutLense(l, input);
    std::transform(zoomed.begin(), zoomed.end(), zoomed.begin(), action);
    return zoomed;
}
*/
    /*
    template <typename Input, typename Output> Lense<Input, Output> lense(const Input& input)
    {
        Lense<Input> l;
        l.kind = LenseKind::Regular;
        l.value = input;
        return l;
    }
*/


} // namespace lenses

typedef lenses::Lense<Amber, ShadowStorms> ShadowStormsLense;
typedef lenses::Lense<ShadowStorms, ShadowStorm> ShadowStormLense;

ShadowStormsLense shadowStormsLense()
{
    lenses::Lense<Amber, ShadowStorms, ShadowStorm> l;
    l.zoomer = [](const Amber& amber)
    {
        return amber.storms;
    };
    return l;
}
/*
const ShadowStormLense shadowStormLense = [](const ShadowStorms& storms)
{
    return lenseEach<ShadowStorms, ShadowStorm>(storms);
};


const ShadowStorm moveShadowStorm = [](const ShadowStorm& storm)
{
    // TODO
    return storm;
};
*/

//zoom<Amber, ShadowStorms>(shadowStormsLense, zoom<ShadowStorms, ShadowStorm>(shadowStormLense, idLense)

} // namespace experimental




MaybeAmber inflateShadowStorms(const Amber& amber)
{
    /*
    MaybeShadowStorms mbShadowStorms = bind<Amber, ShadowStorms>(monad::maybe::just(amber),
        [](const Amber& a)
        {
            return overLense<Amber, ShadowStorms, ShadowStorm>(shadowStormsLense, a, moveShadowStorm);
        });
    // TODO
    */
    return monad::maybe::wrap(amber);
}

#endif // LENSES_H
