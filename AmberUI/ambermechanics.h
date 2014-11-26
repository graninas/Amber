#ifndef AMBERMECHANICS_H
#define AMBERMECHANICS_H

#include "amber.h"
#include "common.h"
#include "maybemonad.h"

namespace amber
{

typedef monad::MonadicValue<monad::maybe::Maybe<Amber>> MaybeAmber;
typedef monad::MonadicValue<monad::maybe::Maybe<Area>> MaybeArea;
typedef monad::MonadicValue<monad::maybe::Maybe<Shadow>> MaybeShadow;
typedef monad::MonadicValue<monad::maybe::Maybe<ShadowStructure>> MaybeShadowStructure;
typedef monad::MonadicValue<monad::maybe::Maybe<ShadowStorm>> MaybeShadowStorm;
typedef monad::MonadicValue<monad::maybe::Maybe<ShadowStorms>> MaybeShadowStorms;
typedef monad::MonadicValue<monad::maybe::Maybe<TimedShadowVariator>> MaybeTimedShadowVariator;

namespace workers
{

Amber goDirection(const Amber& amber, Direction::DirectionType dir);
Amber tickHour(const Amber& amber);
MaybeAmber stabilizeShadow(const Amber& amber);
MaybeAmber inflateShadowStorms(const Amber& amber);
MaybeAmber affectShadowStorms(const Amber& amber);

} // namespace workers

// This boilerplace can be removed by a macro.
const AmberTask goNorth = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::North);
};

const AmberTask goSouth = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::South);
};

const AmberTask goWest = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::West);
};

const AmberTask goEast = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::East);
};

const AmberTask goNorthEast = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::NorthEast);
};

const AmberTask goNorthWest = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::NorthWest);
};

const AmberTask goSouthEast = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::SouthEast);
};

const AmberTask goSouthWest = [](const Amber& amber)
{
    return workers::goDirection(amber, Direction::SouthWest);
};

const AmberTask tickWorldTime = [](const Amber& amber)
{
    return workers::tickHour(amber);
};

// Presentation tip: potential place to lift from one monad to another.
const AmberTask shadowStabilization = [](const Amber& amber)
{
    return monad::maybe::maybe(workers::stabilizeShadow(amber), amber);
};

const AmberTask inflateShadowStorms = [](const Amber& amber)
{
    return monad::maybe::maybe(workers::inflateShadowStorms(amber), amber);
};

const AmberTask affectShadowStorms = [](const Amber& amber)
{
    MaybeAmber mbAmber = workers::affectShadowStorms(amber);
    if (monad::maybe::isNothing(mbAmber))
    {
        qDebug() << "storm has no effect";
        throw std::domain_error("Storm has no effect"); // This is a very, very bad design. Just a showcase.
    }
    return monad::maybe::maybe(mbAmber, amber);
};

namespace experimental
{

namespace LensKind
{
enum LensKindType
{
    Focus,
    Single,
    Multiple
};
}

struct Identity
{
};

template <typename Zoomed1, typename Zoomed2>
struct Lens
{
    LensKind::LensKindType kind;
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
    l.kind = LensKind::Focus;
    return l;
}

template <typename Zoomed1, typename Zoomed2>
Lens<Zoomed1, Zoomed2>
    lens(const std::function<Zoomed2(Zoomed1)>& getter,
         const std::function<Zoomed1(Zoomed1, Zoomed2)>& setter)
{
    Lens<Zoomed1, Zoomed2> l;
    l.kind = LensKind::Single;
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

struct InnerStruct
{
    int i;
};

struct Test
{
    InnerStruct inner;
    std::string s;
};

Lens<Test, InnerStruct> innerL();
Lens<InnerStruct, int> intIL();

Test testLens(const Test& test);

} // experimental

} // namespace amber

#endif // AMBERMECHANICS_H
