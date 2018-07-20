#include "helpers.h"

namespace amber {
namespace model {

Scalar mkScalar(stm::Context& ctx,
                const std::string& name,
                const Value& value,
                const ScalarType& subtype)
{
    Scalar scalar;
    scalar.name    = stm::newTVarIO(ctx, name);
    scalar.value   = stm::newTVarIO(ctx, value);
    scalar.subtype = stm::newTVarIO(ctx, subtype);
    return scalar;
}

Scalar mkItemScalar(stm::Context& ctx,
                    const std::string& name)
{
    return mkScalar(ctx, name, 0, ScalarType::Item);
}

Scalar mkColorScalar(stm::Context& ctx,
                     const std::string& name,
                     const Value& value)
{
    return mkScalar(ctx, name, value, ScalarType::Color);
}

Composite mkComposite(
        stm::Context& ctx,
        const std::string& name,
        const CompositeF& compositeF)
{
    Composite composite;
    composite.name       = stm::newTVarIO(ctx, name);
    composite.composite  = compositeF;
    return composite;
}

Composite mkPercentageComposite(
        stm::Context& ctx,
        const std::string& name,
        const std::map<Name, std::pair<Component, Value>>& percents)
{
    PercentComponents components;
    for (std::pair<Name, std::pair<Component, Value>> p : percents)
    {
        PercentComponent component;
        component.component = stm::newTVarIO(ctx, p.second.first);
        component.percent = stm::newTVarIO(ctx, p.second.second);
        components[p.first] = component;
    }

    PercentageComposite composite;
    composite.components = stm::newTVarIO(ctx, components);
    return mkComposite(ctx, name, composite);
}

Composite mkStructuralComposite(
        stm::Context& ctx,
        const std::string& name,
        const Components& components)
{
    StructuralComposite composite;
    composite.components = stm::newTVarIO(ctx, components);
    return mkComposite(ctx, name, composite);
}

} // namespace model
} // namespace amber
