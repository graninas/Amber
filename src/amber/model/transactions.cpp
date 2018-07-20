#include "transactions.h"

namespace amber {
namespace model {

stm::STML<Name> getComponentName(const Component& component)
{
    if (std::holds_alternative<Composite>(component))
    {
        Composite composite = std::get<Composite>(component);
        return stm::readTVar(composite.name);
    }
    else if (std::holds_alternative<Scalar>(component))
    {
        Scalar scalar = std::get<Scalar>(component);
        return stm::readTVar(scalar.name);
    }
    else
    {
        throw std::runtime_error("Component alternatives not full");
    }
}

stm::STML<MaybePercentComponent>
    findPercentComponent(const Name& name, const Composite& composite)
{
    const PercentageComposite *c = std::get_if<PercentageComposite>(&composite.composite);

    return stm::withTVar<PercentComponents, MaybePercentComponent>
            (c->components, [=](PercentComponents components)
    {
        auto found = components.find(name);
        if (found == components.end())
        {
            return stm::pure<MaybePercentComponent>(std::nullopt);
        }
        return stm::pure<MaybePercentComponent>(found -> second);
    });
}

} // namespace model
} // namespace amber
