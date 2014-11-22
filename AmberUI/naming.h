#ifndef NAMING_H
#define NAMING_H

#include "knownareas.h"

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

std::string AreaName(const std::string& area)
{
    if (area == AmberPoleArea) return "Полюс Амбера";
    if (area == ChaosPoleArea) return "Полюс Хаоса";
    if (area == MiddleShadows) return "Средние тени";
    return "unknown area";
}

std::string ShadowName(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Амбер";
    if (shadow == BergmaShadow) return "Бергма";
    if (shadow == KashfaShadow) return "Кашфа";
    if (shadow == AvalonShadow) return "Авалон";
    return "unknown shadow";
}


}

#endif // NAMING_H
