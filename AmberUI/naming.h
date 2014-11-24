#ifndef NAMING_H
#define NAMING_H

#include "knownareas.h"
#include "amberstructure.h"

namespace naming
{

std::string elementName(amber::Element::ElementType element);
std::string areaName(const std::string& area);
std::string shadowName(const std::string& shadow);
std::string shadowNameForm1(const std::string& shadow);
std::string shadowNameForm2(const std::string& shadow);
std::string shadowNameForm3(const std::string& shadow);

}

#endif // NAMING_H
