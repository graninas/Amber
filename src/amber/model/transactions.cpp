#include "transactions.h"

namespace amber {
namespace model {

//stm::STML<Name> getComponentName(const Component& component)
//{
//    if (std::holds_alternative<Composite>(component))
//    {
//        Composite composite = std::get<Composite>(component);
//        return stm::readTVar(composite.name);
//    }
//    else if (std::holds_alternative<Scalar>(component))
//    {
//        Scalar scalar = std::get<Scalar>(component);
//        return stm::readTVar(scalar.name);
//    }
//    else
//    {
//        throw std::runtime_error("Component alternatives not full");
//    }
//}

//stm::STML<MaybeComponent>
//    findComponent(const Name& name, const Composite& composite)
//{
//    const PercentageComposite *c = std::get_if<PercentageComposite>(&composite.composite);

//    return stm::withTVar<PercentComponents, MaybeComponent>
//            (c->components, [=](PercentComponents components)
//    {
//        auto found = components.find(name);
//        if (found == components.end())
//        {
//            return stm::pure<MaybeComponent>(std::nullopt);
//        }

//        PercentComponent& pc = found -> second;

//        return stm::withTVar<Component, MaybeComponent>(
//                    pc.component,
//                    [](const Component& component)
//                    {
//                        return stm::pure<MaybeComponent>(std::make_optional<Component>(component));
//                    });
//    });
//}

//stm::STML<MaybeScalar>
//    findScalar(const ScalarType& subtype,
//               const Component& component,
//               int level)
//{
//    if (level == 1 && std::holds_alternative<Scalar>(component))
//    {
//        Scalar scalar = std::get<Scalar>(component);
//        return stm::withTVar<ScalarType, MaybeScalar>
//                (scalar.subtype,
//                 [=](ScalarType t)
//        {
//            return stm::pure<MaybeScalar>(
//                        t == subtype
//                        ? std::make_optional<Scalar>(scalar)
//                        : std::nullopt);
//        });
//    }
//    return stm::pure<MaybeScalar>(std::nullopt);
//}

//stm::STML<MaybePercentComponent>
//    findPercentComponent(const Name& name, const Composite& composite)
//{
//    const PercentageComposite *c = std::get_if<PercentageComposite>(&composite.composite);

//    return stm::withTVar<PercentComponents, MaybePercentComponent>
//            (c->components, [=](PercentComponents components)
//    {
//        auto found = components.find(name);
//        if (found == components.end())
//        {
//            return stm::pure<MaybePercentComponent>(std::nullopt);
//        }
//        return stm::pure<MaybePercentComponent>(found -> second);
//    });
//}

} // namespace model
} // namespace amber
