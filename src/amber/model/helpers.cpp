#include "helpers.h"

namespace amber {
namespace model {

Component mkScalar(stm::Context& ctx,
                const std::string& name,
                const Value& value)
{
    Scalar scalar;
    scalar.tName    = stm::newTVarIO(ctx, name);
    scalar.tValue   = stm::newTVarIO(ctx, value);
    return { scalar };
}

Component mkComposite(
        stm::Context& ctx,
        const std::string& name,
        const Components& components)
{
    Composite composite;
    composite.tName       = stm::newTVarIO(ctx, name);
    composite.tComponents = stm::newTVarIO(ctx, components);
    return { composite };
}

World mkWorld(
        stm::Context& ctx,
        const std::string& name,
        const Components& components)
{
    Composite worldStructure;
    worldStructure.tComponents = stm::newTVarIO(ctx, components);
    worldStructure.tName       = stm::newTVarIO(ctx, std::string("Structure"));

    World world;
    world.name = name;
    world.tRoles = stm::newTVarIO(ctx, Roles {});
    world.structure = worldStructure;

    return world;
}

} // namespace model
} // namespace amber
