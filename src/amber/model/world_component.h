#ifndef WORLD_COMPONENT_H
#define WORLD_COMPONENT_H

#include <functional>
#include <stm.h>

namespace amber {
namespace model {

// forward declaration
struct Composite;
struct Percentage;

template <typename T>
struct Scalar
{
//    stm::ReadOnlyTVar<uint32_t> nameIndex;
    stm::TVar<std::string> name;


    stm::TVar<T> value;
};

using FScalarT = double;
using IScalarT = int64_t;

using FScalar = Scalar<FScalarT>;
using IScalar = Scalar<IScalarT>;

using Component = std::variant<Composite, Percentage, IScalar, FScalar>;

using CompositeComponents  = std::vector<Component>;
using PercentageComponents = std::vector<IScalar>;

struct Percentage
{
    //    stm::ReadOnlyTVar<uint32_t> nameIndex;
    stm::TVar<std::string> name;

    // Number of components may vary
    stm::TVar<PercentageComponents> components;
};

struct Composite
{
//    stm::ReadOnlyTVar<uint32_t> nameIndex;
    stm::TVar<std::string> name;

    // Number of components may vary
    stm::TVar<CompositeComponents> components;
};

//world1 :: World
//{
//    gravity = 2;
//    dayLen = 24;
//}

//world1_voxel_1_1 :: Composite
//{
//    localTime = 12;
//    sky = Composite { color = 1; };
//    air = Composite
//        {
//            Percentage
//            {
//                oxygen = 24;
//                nitrogen = 72;
//                water = 4;
//            }
//        };
//    ground = Composite
//        {
//            Percentage
//            {
//                soil = 60;
//                stones = 35;
//            }
//            Percentage
//            {
//                grass = 30;
//            }
//        }
//};

//struct World
//{
//    static:
//    gravity :: Scalar
//    dayLen :: Scalar

//    voxel :: CompositeF 3
//    {
//        localTime :: Scalar (depends on dayLen)
//        level2 sky :: CompositeF N1
//        level1 air :: CompositeF N2
//        level0 ground :: CompositeF N3
//    }
//};

template <typename T>
Scalar<T> mkScalar(stm::Context& ctx, const std::string& name, const T& val)
{
    Scalar<T> scalar;
    scalar.name  = stm::newTVarIO(ctx, name);
    scalar.value = stm::newTVarIO(ctx, val);
    return scalar;
}

IScalar mkIScalar(stm::Context& ctx, const std::string& name, const IScalarT& val)
{
    return mkScalar<IScalarT>(ctx, name, val);
}

FScalar mkFScalar(stm::Context& ctx, const std::string& name, const FScalarT& val)
{
    return mkScalar<FScalarT>(ctx, name, val);
}

Percentage mkPercentage(stm::Context& ctx,
                        const std::string& name,
                        const PercentageComponents& components)
{
    Percentage percentage;
    percentage.name       = stm::newTVarIO(ctx, name);
    percentage.components = stm::newTVarIO(ctx, components);
    return percentage;
}

Composite mkComposite(stm::Context& ctx,
                      const std::string& name,
                      const CompositeComponents& components)
{
    Composite composite;
    composite.name       = stm::newTVarIO(ctx, name);
    composite.components = stm::newTVarIO(ctx, components);
    return composite;
}

} // namespace model
} // namespace amber

#endif // WORLD_COMPONENT_H
