#ifndef NAMING_H
#define NAMING_H

#include "shadowstructure.h"

namespace naming
{

using namespace amber;

std::string ElementName(Element::ElementType element)
{
    switch (element)
    {
    case Element::Air: return "Air";
    case Element::AmberDistance: return "Amber Distance";
    case Element::ChaosDistance: return "Chaos Distance";
    case Element::Fauna: return "Fauna";
    case Element::Flora: return "Flora";
    case Element::Ground: return "Ground";
    case Element::Sky: return "Sky";
    case Element::Water: return "Water";
    }
    return "unknown element";
}


}

#endif // NAMING_H
