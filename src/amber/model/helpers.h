#ifndef HELPERS_H
#define HELPERS_H

#include <functional>
#include <list>
#include <stm/stm.h>

#include "model.h"
#include "transactions.h"

namespace amber {
namespace model {

const auto isColorScalarType = [](ScalarType scalarType)
{
    return ScalarType::Color == scalarType;
};

const auto isValidColor = [](Value value)
{
    return (value <= 0xffffffff) && (value >= 0);
};

const auto isPercentageComposite = [](const Composite& composite)
{
    return std::holds_alternative<PercentageComposite>(composite.composite);
};

Scalar mkScalar(stm::Context& ctx,
                const std::string& name,
                const Value& value,
                const ScalarType& subtype = ScalarType::Value);

Scalar mkItemScalar(stm::Context& ctx,
                    const std::string& name);

Scalar mkColorScalar(stm::Context& ctx,
                     const std::string& name,
                     const Value& value);

Composite mkComposite(
        stm::Context& ctx,
        const std::string& name,
        const CompositeF& compositeF);

Composite mkPercentageComposite(stm::Context& ctx,
        const std::string& name,
        const std::map<Name, std::pair<Component, Value> > &percents);

Composite mkStructuralComposite(
        stm::Context& ctx,
        const std::string& name,
        const Components& components);

} // namespace model
} // namespace amber

#endif // HELPERS_H
