#include "assets.h"

#include "common.h"

namespace amber
{

namespace known_shadows
{

struct ShadowDescriptor
{
    std::string shadowName;
    ShadowStructure shadowStructure;
    ShadowChanger shadowChanger;
};

typedef std::vector<ShadowDescriptor> KnownShadowDescriptors;

ShadowDescriptor amberShadow()
{
    ShadowDescriptor descritptor;
    descritptor.shadowName = "Amber";
    descritptor.shadowStructure.insert({
                                           ShadowStructure::value_type(Element::Air, 50)
                                       });
    // TODO
    // descritptor.shadowChanger
    return descritptor;
}

KnownShadowDescriptors knownShadowDescriptors()
{
    return {
        amberShadow(),
        amberShadow()
    };
}

}

Amber defaultAmber()
{
    Amber amber;
    amber.hoursElapsed = 0;
//    amber.direction = PoleAmber;
//    amber.worldPolePosition = 50;

    // TODO: shadows
    return amber;
}

}
