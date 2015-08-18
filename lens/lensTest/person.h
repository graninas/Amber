#ifndef PERSON_H
#define PERSON_H

#include "common.h"
#include "address.h"

#include "../lenses.h"
#include "../autolens.h"

namespace sample
{

using namespace lenses;

struct Person
{
    std::string name;
    std::string surname;
    int age;
    Address address;
};



MK_LENS(Person, std::string, name)
MK_LENS(Person, std::string, surname)
MK_LENS(Person, int, age)
MK_LENS(Person, Address, address)

} // namespace sample

#endif // PERSON_H
