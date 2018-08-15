#ifndef MODEL_H
#define MODEL_H

#include <functional>
#include <list>
#include <stm/stm.h>

namespace amber {
namespace model {

using Value = int64_t;
using Name = std::string;

// Forward declaration

struct Scalar;
struct Component;

// Model

using Components = std::list<Component>;

using TVarString = stm::TVar<std::string>;
using TVarValue = stm::TVar<Value>;
using TVarComponents = stm::TVar<Components>;

struct Scalar
{
    TVarString tName;
    TVarValue tValue;
};

struct Composite
{
    TVarString tName;
    TVarComponents tComponents;
};

struct Component
{
    std::variant<Composite, Scalar> component;
};

enum class RoleType
{
    Percentage = 0,
};

using TVarRoleType = stm::TVar<RoleType>;
using TVarValues = stm::TVar<std::list<TVarValue>>;

struct Role
{
    TVarRoleType tRole;
    TVarValues tValues;
};

using Roles = std::list<Role>;
using TVarRoles = stm::TVar<Roles>;

struct World
{
    std::string name;
    Composite structure;
    TVarRoles tRoles;
};

enum class TVarType
{
    String = 0,
    Value = 1,
    Values = 2,
    Components = 3,
    RoleType = 4,
    Roles = 5,
};

} // namespace model
} // namespace amber

#endif // MODEL_H
