#ifndef MODEL_H
#define MODEL_H

#include <functional>
#include <list>
#include <stm.h>

namespace amber {
namespace model {

using Value = int64_t;
using Name = std::string;

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
    stm::TVar<Value> value;
    stm::TVar<ScalarType> subtype;
};

template <typename T>
using ContainerType = std::list<T>;

using Component = std::variant<Composite, Scalar>;
using Components = ContainerType<Component>;
//using Components = std::map<Name, Component>;

struct PercentComponent
{
    stm::TVar<Component> component;
    stm::TVar<Value> percent;
};

using PercentComponents = std::map<Name, PercentComponent>;

struct PercentageComposite
{
    stm::TVar<PercentComponents> components;
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

} // namespace model
} // namespace amber

#endif // MODEL_H
