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

    // TODO: invent a safe version of ShadowStructure (with templates magic possibly).
    // Make safeStructureChange() unnecessary.
    // Show it in presentation.
    descritptor.shadowStructure.insert({
                                           element::AmberDistance(0)
                                         , element::ChaosDistance(100)
                                         , element::Air(50)
                                         , element::Ground(50)
                                         , element::Sky(100)
                                         , element::Water(50)
                                         , element::Flora(100)
                                         , element::Fauna(100)
                                       });
    descritptor.shadowVariator = [](const ShadowStructure& structure, Direction::DirectionType direction)
    {
        int waterGroundNSChange = 2;
        int waterGroundWEChange = 1;
        int amberChaosDistanceChange = 1;

        // N.B.! This can be wrapped into a small 'Changing DSL'.
        // Invent a pairs of dependant elements, for example water-ground, sky-air, amber-chaos.
        // Show it in presentation.
        ShadowStructure newStructure = structure;
        switch (direction)
        {
        case Direction::North:
            safeStructureChange(newStructure, Element::Water,         -waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundNSChange);
            safeStructureChange(newStructure, Element::AmberDistance,  amberChaosDistanceChange);
        case Direction::South:
            safeStructureChange(newStructure, Element::Water,          waterGroundNSChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundNSChange);
            safeStructureChange(newStructure, Element::ChaosDistance, -amberChaosDistanceChange);
        case Direction::East:
            safeStructureChange(newStructure, Element::Water,         -waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,         waterGroundWEChange);
            safeStructureChange(newStructure, Element::AmberDistance,  amberChaosDistanceChange);
        case Direction::West:
            safeStructureChange(newStructure, Element::Water,          waterGroundWEChange);
            safeStructureChange(newStructure, Element::Ground,        -waterGroundWEChange);
            safeStructureChange(newStructure, Element::ChaosDistance, -amberChaosDistanceChange);
        };

        return newStructure;
    };

    return descritptor;
} // namespace known_shadows

KnownShadowDescriptors knownShadowDescriptors()
{
    return
    {
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
    return amber;
}

}
