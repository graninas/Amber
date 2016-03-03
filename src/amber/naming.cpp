#include "naming.h"

namespace naming
{

using namespace amber;

std::string elementName(Element::ElementType element)
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

std::string areaName(const std::string& area)
{
    if (area == AmberPoleArea) return "Amber Pole";
    if (area == ChaosPoleArea) return "Chaos Pole";
    if (area == MiddleShadows) return "Middle Shadows";
    return "unknown area";
}

std::string shadowName(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Amber";
    if (shadow == BergmaShadow) return "Begma";
    if (shadow == KashfaShadow) return "Kashfa";
    if (shadow == AvalonShadow) return "Avalon";
    return "unknown shadow";
}

std::string shadowNameForm1(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Amber";
    if (shadow == BergmaShadow) return "Begma";
    if (shadow == KashfaShadow) return "Kashfa";
    if (shadow == AvalonShadow) return "Avalon";
    return "unknown shadow";
}

std::string shadowNameForm2(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Amber";
    if (shadow == BergmaShadow) return "Begma";
    if (shadow == KashfaShadow) return "Kashfa";
    if (shadow == AvalonShadow) return "Avalon";
    return "unknown shadow";
}

std::string shadowNameForm3(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Amber";
    if (shadow == BergmaShadow) return "Begma";
    if (shadow == KashfaShadow) return "Kashfa";
    if (shadow == AvalonShadow) return "Avalon";
    return "unknown shadow";
}

}
