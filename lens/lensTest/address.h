#ifndef ADDRESS_H
#define ADDRESS_H

#include "common.h"
#include "../lenses.h"
#include "../autolens.h"

namespace sample
{
using namespace lenses;

struct Address
{
    std::string city;
    std::string street;
    int house;
    int flat;
};


MK_LENS(Address, std::string, city)
MK_LENS(Address, std::string, street)
MK_LENS(Address, int, house)
MK_LENS(Address, int, flat)

/*
Lens<Address, int> houseL() {
    return lens<Address, int> ( GETTER(Address, house)
                              , SETTER(Address, int, house));
}
*/


} // namespace sample


#endif // ADDRESS_H
