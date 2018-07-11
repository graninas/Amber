#ifndef WORLD_COMPONENT_H
#define WORLD_COMPONENT_H

#include <functional>
#include <stm.h>

namespace amber {
namespace model {

// forward declaration
struct Composite;

template <typename T>
struct Scalar
{
//    stm::ReadOnlyTVar<uint32_t> nameIndex;
    stm::TVar<T> value;
};

using FScalar = Scalar<double>;
using IScalar = Scalar<int64_t>;

using Component = std::variant<Composite, IScalar, FScalar>;
using Components = std::vector<Component>;

struct Composite
{
//    stm::ReadOnlyTVar<uint32_t> nameIndex;
    stm::TVar<Components> components;
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




} // namespace model
} // namespace amber

#endif // WORLD_COMPONENT_H
