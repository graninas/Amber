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

stm::STML<Name> getComponentName(const Component& component);

stm::STML<MaybePercentComponent>
    findPercentComponent(const Name& name, const Composite& composite);

} // namespace model
} // namespace amber

#endif // TRANSACTIONS_H
