#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <functional>
#include <list>
#include <stm.h>

#include "model.h"

namespace amber {
namespace model {

using MaybePercentComponent = std::optional<PercentComponent>;
using MaybeValue = std::optional<Value>;
using MaybeComponent = std::optional<Component>;
using MaybeScalar = std::optional<Scalar>;

stm::STML<Name> getComponentName(const Component& component);

stm::STML<MaybeComponent>
    findComponent(const Name& name, const Composite& composite);

stm::STML<MaybeScalar>
    findScalar(const ScalarType& subtype,
               const Component& component,
               int level = 1);

stm::STML<MaybePercentComponent>
    findPercentComponent(const Name& name, const Composite& composite);

} // namespace model
} // namespace amber

#endif // TRANSACTIONS_H
