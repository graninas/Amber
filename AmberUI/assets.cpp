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
    ShadowVariator shadowVariator;
};

typedef std::vector<ShadowDescriptor> KnownShadowDescriptors;

ShadowDescriptor amberShadow()
{
    ShadowDescriptor descritptor;
    descritptor.shadowName = "Amber";
    descritptor.shadowStructure.insert({
                                           element::AmberDistance(0)
                                         , element::ChaosDistance(100)
                                         , element::Air(50)
                                         , element::Ground(50)
                                         , element::Sky(100)
                                         , element::Flora(100)
                                         , element::Fauna(100)
                                       });
    descritptor.shadowVariator = [](const ShadowStructure& structure, Direction::DirectionType /*direction*/)
    {
        return structure;
    };

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
