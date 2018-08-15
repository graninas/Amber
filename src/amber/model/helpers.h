#ifndef HELPERS_H
#define HELPERS_H

#include <functional>
#include <list>
#include <stm/stm.h>

#include "model.h"
#include "transactions.h"

namespace amber {
namespace model {

Component mkScalar(stm::Context& ctx,
                const std::string& name,
                const Value& value);

Component mkComposite(
        stm::Context& ctx,
        const std::string& name,
        const Components& components);

World mkWorld(
        stm::Context& ctx,
        const std::string& name,
        const Components& components);

} // namespace model
} // namespace amber

#endif // HELPERS_H
