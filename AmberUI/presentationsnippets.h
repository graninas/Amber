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

// Evaluate tasks

void View::goNorthAction()
{
    AmberTaskList tasks = {
        goNorth,
        tickWorldTime
    };

    changeAmber(tasks);
}

void View::changeAmber(const AmberTaskList& tasks)
{
    Amber currentAmber = m_amber;

    std::for_each(tasks.begin(), tasks.end(),
        [&currentAmber](const AmberTask& task)
        {
            currentAmber = task(currentAmber);
        });

    m_amber = currentAmber;
}

// unsafe code

const AmberTask inflateShadowStorms =
        [](const Amber& amber)
{
    throw std::runtime_error("Shit happened!");
};

// combinatorial eDSL

void View::tickOneAmberHour() {

    AmberTask combinedTask =
            [](const Amber& amber)
    {
        auto action1Res = anyway(inflateShadowStorms, wrap(amber));
        auto action2Res = anyway(affectShadowStorms, action1Res);
        auto action3Res = onFail(shadowStabilization, action2Res);
        auto action4Res = anyway(tickWorldTime, action3Res);
        return action4Res.amber;
    };

    changeAmber(combinedTask);
}


} // presentationsnippets

#endif // PRESENTATIONSNIPPETS_H
