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
    if (area == AmberPoleArea) return "Полюс Амбера";
    if (area == ChaosPoleArea) return "Полюс Хаоса";
    if (area == MiddleShadows) return "Средние тени";
    return "unknown area";
}

std::string shadowName(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Амбер";
    if (shadow == BergmaShadow) return "Бергма";
    if (shadow == KashfaShadow) return "Кашфа";
    if (shadow == AvalonShadow) return "Авалон";
    return "unknown shadow";
}

std::string shadowNameForm1(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Амбера";
    if (shadow == BergmaShadow) return "Бергмы";
    if (shadow == KashfaShadow) return "Кашфы";
    if (shadow == AvalonShadow) return "Авалона";
    return "unknown shadow";
}

std::string shadowNameForm2(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Амберу";
    if (shadow == BergmaShadow) return "Бергме";
    if (shadow == KashfaShadow) return "Кашфу";
    if (shadow == AvalonShadow) return "Авалону";
    return "unknown shadow";
}

std::string shadowNameForm3(const std::string& shadow)
{
    if (shadow == AmberShadow)  return "Амбер";
    if (shadow == BergmaShadow) return "Бергму";
    if (shadow == KashfaShadow) return "Кашфу";
    if (shadow == AvalonShadow) return "Авалон";
    return "unknown shadow";
}

}
