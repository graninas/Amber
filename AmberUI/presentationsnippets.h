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

}

using namespace aux;
using namespace amber;
using namespace element;


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

} // presentationsnippets

#endif // PRESENTATIONSNIPPETS_H
