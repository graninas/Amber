#include "world1.h"

using namespace amber::model;
namespace amber {
namespace assets {

World world1(stm::Context& ctx)
{
    Component skyColor = mkScalar(ctx, "sky color", 0);

    Component sky = mkComposite(ctx, "sky", {skyColor});

    Component oxygenPercent   = mkScalar(ctx, "oxygen percent",   24);
    Component nitrogenPercent = mkScalar(ctx, "nitrogen percent", 72);
    Component waterPercent    = mkScalar(ctx, "water percent",    4);

    Component air = mkComposite(ctx, "air", {oxygenPercent, nitrogenPercent, waterPercent});

    Component soilColor   = mkScalar(ctx, "soil color",   0x66ffff00);
    Component stonesColor = mkScalar(ctx, "stones color", 0x66ffff00);
    Component grassColor  = mkScalar(ctx, "grass color",  0x66ffff00);

    Component groundColor = mkComposite(ctx, "ground color", {soilColor, stonesColor, grassColor});

    Component soilPercent   = mkScalar(ctx, "soil percent",   60);
    Component stonesPercent = mkScalar(ctx, "stones percent", 35);
    Component grassPercent  = mkScalar(ctx, "grass percent",  5);

    Component groundPercentage = mkComposite(ctx, "ground percentage", {soilPercent, stonesPercent, grassPercent});

    Component ground = mkComposite(ctx, "ground", {groundColor, groundPercentage});

    World world = mkWorld(ctx, "World", {sky, air, ground});

    return world;
}

}}
