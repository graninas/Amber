#ifndef WORLD_COMPONENT_H
#define WORLD_COMPONENT_H

#include <functional>
#include <list>
#include <stm.h>

namespace amber {
namespace model {

using ValueT = int64_t;

// forward declaration
struct Composite;

enum class ScalarType
{
    Value,
    Color,
    Item
};

struct Scalar
{
    stm::TVar<std::string> name;
    stm::TVar<ValueT> value;
    stm::TVar<ScalarType> subtype;
};

template <typename T>
using ContainerType = std::list<T>;

using Component = std::variant<Composite, Scalar>;
using Components = ContainerType<Component>;
using Percents = ContainerType<ValueT>;

struct PercentageComposite
{
    stm::TVar<Percents> percents;
    stm::TVar<Components> components;
};

struct StructuralComposite
{
    stm::TVar<Components> components;
};

using CompositeF = std::variant<StructuralComposite, PercentageComposite>;

struct Composite
{
    stm::TVar<std::string> name;
    CompositeF composite;
};

Scalar mkScalar(stm::Context& ctx,
                const std::string& name,
                const ValueT& value,
                const ScalarType& subtype = ScalarType::Value)
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
                     const ValueT& value)
{
    return mkScalar(ctx, name, value, ScalarType::Color);
}

struct PercentHelper
{
    Component component;
    ValueT percent;
};

PercentHelper mkPercent(const Component& component, const ValueT& percent)
{
    return PercentHelper { component, percent };
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
        const std::vector<PercentHelper>& percentHelpers)
{
    Components components;
    Percents percents;
    for (const PercentHelper& percentHelper : percentHelpers)
    {
        components.push_back(percentHelper.component);
        percents.push_back(percentHelper.percent);
    }

    PercentageComposite composite;
    composite.components = stm::newTVarIO(ctx, components);
    composite.percents = stm::newTVarIO(ctx, percents);
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

#endif // WORLD_COMPONENT_H
