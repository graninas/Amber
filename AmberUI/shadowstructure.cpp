#include "shadowstructure.h"

namespace amber
{

namespace element
{

ShadowStructure::value_type AmberDistance(int distance)
{
    return ShadowStructure::value_type(Element::AmberDistance, distance);
}

ShadowStructure::value_type ChaosDistance(int distance)
{
    return ShadowStructure::value_type(Element::ChaosDistance, distance);
}

ShadowStructure::value_type Air(int air)
{
    return ShadowStructure::value_type(Element::Air, air);
}

ShadowStructure::value_type Sky(int sky)
{
    return ShadowStructure::value_type(Element::Sky, sky);
}

ShadowStructure::value_type Ground(int ground)
{
    return ShadowStructure::value_type(Element::Ground, ground);
}

ShadowStructure::value_type Water(int water)
{
    return ShadowStructure::value_type(Element::Water, water);
}

ShadowStructure::value_type Flora(int flora)
{
    return ShadowStructure::value_type(Element::Flora, flora);
}

ShadowStructure::value_type Fauna(int fauna)
{
    return ShadowStructure::value_type(Element::Fauna, fauna);
}


}

}
