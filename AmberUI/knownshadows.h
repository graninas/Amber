#ifndef KNOWNSHADOWS_H
#define KNOWNSHADOWS_H

#include "amber.h"
#include "common.h"

namespace amber
{

const std::string AmberShadow = "AmberShadow";
const std::string TrueAmber = "Amber";
const std::string BergmaShadow = "BergmaShadow";
const std::string TrueBergma = "Bergma";

ShadowStructure amberShadowStructure()
{
    return {
        element::AmberDistance(1)
      , element::ChaosDistance(99)
      , element::Air(50)
      , element::Ground(50)
      , element::Sky(100)
      , element::Water(30)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowStructure trueAmberStructure()
{
    return {
        element::AmberDistance(0)
      , element::ChaosDistance(100)
      , element::Air(60)
      , element::Ground(80)
      , element::Sky(80)
      , element::Water(20)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowStructure bergmaShadowStructure()
{
    return {
        element::AmberDistance(2)
      , element::ChaosDistance(98)
      , element::Air(60)
      , element::Ground(80)
      , element::Sky(90)
      , element::Water(20)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

ShadowStructure trueBergmaStructure()
{
    return {
        element::AmberDistance(2)
      , element::ChaosDistance(98)
      , element::Air(70)
      , element::Ground(90)
      , element::Sky(100)
      , element::Water(10)
      , element::Flora(100)
      , element::Fauna(100)
  };
}

} // namespace amber



#endif // KNOWNSHADOWS_H
