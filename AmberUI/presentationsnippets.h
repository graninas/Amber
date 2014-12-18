#ifndef PRESENTATIONSNIPPETS_H
#define PRESENTATIONSNIPPETS_H

#include "amber.h"
#include "monads.h"
#include "shadowmechanics.h"

namespace presentationsnippets
{

namespace aux
{

class ShadowsView
{
public:
    void tickOneAmberHour();
};

class View
{
public:
    void tickOneAmberHour();
};

typedef std::list<AmberTask> AmberTaskList;

typedef monad::maybe::Maybe<Amber> MaybeAmber;
typedef monad::maybe::Maybe<Area> MaybeArea;
typedef monad::maybe::Maybe<Shadow> MaybeShadow;
typedef monad::maybe::Maybe<ShadowStructure> MaybeShadowStructure;
typedef monad::maybe::Maybe<ShadowVariator> MaybeShadowVariator;
typedef monad::maybe::Maybe<ShadowStorm> MaybeShadowStorm;
typedef monad::maybe::Maybe<ShadowStorms> MaybeShadowStorms;
typedef monad::maybe::Maybe<TimedShadowVariator> MaybeTimedShadowVariator;

struct Test{
    void changeElementTest();
};

}

using namespace aux;
using namespace amber;
using namespace element;
using namespace monad;
using namespace maybe;


// Snippets

// Declaraive world settings

namespace Element
{
enum ElementType
{
    Air,
    Sky,
    Water,
    Ground
};
}

typedef std::map<Element::ElementType, int> ShadowStructure;

ShadowStructure amberShadowStructure()
{
    return {
        { Element::Ground, 90 }
      , { Element::Water, 10 }
      ,   element::Air(100)
      ,   element::Sky(70)
    };
}

typedef std::function<ShadowStructure(ShadowStructure,
                                      Direction::DirectionType)>
    ShadowVariator;

struct Shadow {
   ShadowName name;
   ShadowVariator variator;
   ShadowStructure structure;
   double influence;
};

//ShadowVariator :: ShadowStructure -> Direction -> ShadowStructure

const ShadowVariator identityVariator =
        [](const ShadowStructure& structure,
           Direction::DirectionType)
{
    return structure;
};


const ShadowVariator amberVariator =
        [](const ShadowStructure& structure,
           Direction::DirectionType) -> ShadowStructure {

    switch (direction) {
    case Direction::North:
        return changeElements({ element::Water(-2)
                              , element::Ground(2) }
                              , structure);
            // etc
    }
};



ShadowStructure amberModifiers() {
   switch (direction) {
   case Direction::North:
       return { {Element::Water,  -2 }
              , {Element::Ground,  2 } };

   }
}


// AmberTask
typedef std::function<Amber (const Amber&)> AmberTask;

const AmberTask goNorth = [](const Amber& amber)
{
    const Shadow& shadow = getNearestShadow(amber);

    Amber newAmber = amber;
    newAmber.playerShadowStructure =
            shadow.variator(amber.playerShadowStructure, Direction::North);
    return newAmber;
};

// Lambdas constructing

const AmberTask goNorth = [](const Amber& amber)
{
    // Bla-bla
};

AmberTask goDirection(Direction::DirectionType dir)
{
    return [=](const Amber& amber) {
        // Bla-bla
    };
}

// List of tasks

Amber goNorth(const Amber& amber) {

   AmberTaskList tasks = {
       goNorth,
       inflateShadowStorms,
       tickWorldTime
   };

   return evaluate(amber, tasks);
}

Amber evaluate(const Amber& amber,
                          const AmberTaskList& tasks) {

 Amber currentAmber = amber;

   std::for_each(tasks.begin(), tasks.end(),
       [&currentAmber](const AmberTask& task) {
           currentAmber = task(currentAmber);
       });

   return currentAmber;
}



// unsafe code

const AmberTask inflateShadowStorms =
        [](const Amber& amber)
{
    throw std::runtime_error("Shit happened!");
};

// combinatorial eDSL

void View::tickOneAmberHour() {

    AmberTask tickOneAmberHour = [](const Amber& amber) {
        auto action1Res = anyway(inflateShadowStorms, wrap(amber));
        auto action2Res = anyway(affectShadowStorms,  action1Res);
        auto action3Res = onFail(shadowStabilization, action2Res);
        auto action4Res = anyway(tickWorldTime, action3Res);
        return action4Res.amber;
    };

    changeAmber(combinedTask);
}

AmberTask goNorthTask = [](const Amber& amber) {
    auto action1Res = anyway(goNorth,          wrap(amber));
    auto action2Res = anyway(tickOneAmberHour, action1Res);
    return action2Res.amber;
};

void View::sleep8Hours() {

    AmberTask sleep6Hours = [](const Amber& amber) {
        auto res1 = anyway(tickOneAmberHour, wrap(amber));
        auto res2 = anyway(tickOneAmberHour, res1);
        auto res3 = anyway(tickOneAmberHour, res2);
        auto res4 = anyway(tickOneAmberHour, res3);
        auto res5 = anyway(tickOneAmberHour, res4);
        auto res6 = anyway(tickOneAmberHour, res5);
        return res6.amber;
    };

    changeAmber(combinedTask);
}

struct Artifact {
    amber::Amber amber;
    bool success;
    std::vector<std::string> systemLog;
};

Artifact wrap(const Amber& amber) {
    Artifact artifact { amber, true, {} };
    return artifact;
}

Artifact anyway(const AmberTask& task,
                const Artifact& artifact) {
    return eval(task, artifact);
}

Artifact onFail(const AmberTask& task,
                const Artifact& artifact)
{
    // eval when artifact.success == false
    // otherwise, return artifact
}

Artifact eval(const AmberTask& task, const Artifact& artifact)
{
    Artifact newArtifact = artifact;
    try {
        Amber newAmber = task(artifact.amber);
        newArtifact.amber = newAmber;
        newArtifact.success = true;
    }
    catch (const std::exception& e) {
        newArtifact.systemLog.push_back(e.what());
        newArtifact.success = false;
    }
    return newArtifact;
}

// Generalization 1

struct Artifact {
    amber::Amber amber;
    bool success;
};

template <class D> struct Value
{
    D data;
    bool success;
};

typedef Value<amber::Amber> SafeAmber;
typedef std::function<SafeAmber(amber::Amber)> SafeAmberTask;

SafeAmber wrap(const amber::Amber& data) {
    return SafeAmber { data, true };
}

SafeAmber bind(const SafeAmber value,
               const SafeAmberTask& task) {
    if (value.success) {
        return task(value.data);
    }
    return SafeAmber { value, false };
}

const SafeAmberTask safeMovePlayerNorth =
    [](const amber::Amber& amber) {
        // Do stuff
    };

SafeAmber moveNorth(const amber::Amber& amber) {
    SafeAmber safeAmber = wrap(amber);
    safeAmber = bind(safeAmber, safeMovePlayerNorth);
    safeAmber = bind(safeAmber, safeUpdateNearestPlace);
    return safeAmber;
}

// Maybe monad

// Monadic functions

const std::function<Maybe<ShadowVariator>(Amber)>
   lookupVariator = [](const Amber& amber) {
   return ...; // Retrieve the nearest shadow's variator
};

std::function<MaybeAmber(ShadowVariator)>
    applyVariator(const Amber& amber,
                  Direction::DirectionType dir) {
    return [&amber, dir](const ShadowVariator& variator) {
        // apply variator to passed amber, using dir
    };
}


// Using monad

MaybeAmber goDirectionBinded1(const Amber& amber,
                              Direction::DirectionType dir) {
   MaybeAmber mbAmber1            = just(amber);
   MaybeShadowVariator mbVariator = bind(mbAmber1,   lookupVariator);
   MaybeAmber mbAmber2            = bind(mbVariator, applyVariator(amber, dir));
   MaybeAmber mbAmber3            = bind(mbAmber2,   updateNearestPlace);
   return mbAmber3;
}

MaybeAmber goDirectionBinded2(const Amber& amber,
                              Direction::DirectionType dir)
{
   auto m1 = mb::just(amber);
   auto m2 = mb::bind(m1, lookupVariator);
   auto m3 = mb::bind(m2, applyVariator(amber, dir));
   auto m4 = mb::bind(m3, updateNearestPlace);
   return m4;
}

// Bind many

MaybeAmber goDirectionStacked(const Amber& amber,
                         Direction::DirectionType dir) {
    MaybeActionStack<Amber, ShadowVariator, Amber, Amber>
        stack = bindMany(lookupShadowVariator,
                         applyMovingVariator(amber, dir),
                         safeUpdateNearestPlace);

    MaybeAmber mbAmber = evalMaybes(just(amber), stack);
    return mbAmber;
}

// MaybeActionStack implementation

struct Identity {}; // Helper, can be of any type

template <typename M1, typename M2,
          typename M3 = Identity, typename M4 = Identity>
struct MaybeActionStack {
   std::function<Maybe<M2>(M1)> action1;
   std::function<Maybe<M3>(M2)> action2;
   std::function<Maybe<M4>(M3)> action3;
};

template <typename M1, typename M2, typename M3, typename M4>
 MaybeActionStack<M1, M2, M3, M4>
    bindMany(const std::function<Maybe<M2>(M1)> action1,
             const std::function<Maybe<M3>(M2)> action2,
             const std::function<Maybe<M4>(M3)> action3)
{
    MaybeActionStack<M1, M2, M3, M4> stack;
    stack.action1 = action1;
    stack.action2 = action2;
    stack.action3 = action3;
    return stack;
}

template <typename M1, typename M2, typename M3, typename M4>
Maybe<M4> evalMaybes(const Maybe<M1>& m1,
                     const MaybeActionStack<M1, M2, M3, M4>& stack)
{
    Maybe<M2> m2 = bind<M1, M2>(m1, stack.action1);
    Maybe<M3> m3 = bind<M2, M3>(m2, stack.action2);
    Maybe<M4> m4 = bind<M3, M4>(m3, stack.action3);
    return m4;
}

// Lenses

struct Person {
    int age;
    std::string firstName;
    std::string lastName;
};

struct Passport {
    Person person;
    std::string number;
};

struct DriverLicense
{
    Person person;
    std::string number;
};

struct PersonalDocuments {
    Passport passport;
    DriverLicense driverLicense;
};


struct C {
    int intC;
    std::string stringC;
};

struct B {
    C c;
};

struct A {
    B b;
};

// The Law of Demeter violation!
void Func()
{
    A a;
    a.b.c.intC = 20;
    a.b.c.stringC = "Hello, World!";

}

A func(const A& oldA)
{

    C newC = oldA.b.c;
    newC.intC = 20;
    newC.stringC = "Hello, world!";

    B newB = oldA.b;
    newB.c = newC;

    A newA = oldA;
    newA.b = newB;

    return newA;
}


// Testing

void Testing::changeElementTest() {
    amber::ShadowStructure structure =
        { { amber::Element::Ground, 90 }
        , { amber::Element::Water, 10 } };

    amber::ShadowStructure expected =
        { { amber::Element::Ground, 100 }
        , { amber::Element::Water, 10 } };

    auto newStructure = changeElement(structure, amber::Element::Ground, 10);
    ASSERT_EQ(expected, newStructure);
}

} // presentationsnippets

#endif // PRESENTATIONSNIPPETS_H
