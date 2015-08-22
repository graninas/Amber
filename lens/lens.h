#ifndef LENS_H
#define LENS_H

#include <functional>

#include "identity.h"

namespace lenses
{

template <typename Value, typename Focus, template <typename> class Container = Identity>
struct Lens
{
    std::function<Focus(Value)> getter;
    std::function<Value(Value&, Focus)> setter;
};

template <typename Value, typename Focus>
Lens<Value, Focus>
    lens(const std::function<Focus(Value)>& getter,
         const std::function<Value(Value, Focus)>& setter)
{
    Lens<Value, Focus> l;
    l.getter = getter;
    l.setter = setter;
    return l;
}

template <typename Value, typename Focus>
    bool isFocus(const Lens<Value, Focus>& l)
{
    return false;
}

template <typename Focus>
    bool isFocus(const Lens<Focus, Id>& l)
{
    return true;
}

template <typename Focus>
Lens<Focus, Id> idL()
{
    Lens<Focus, Id> l;
    return l;
}

}

#endif // LENS_H
