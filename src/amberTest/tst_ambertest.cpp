#include <QString>
#include <QtTest>

#include <stm.h>

#include "../amber/model/world_component.h"

class AmberTest : public QObject
{
    Q_OBJECT

public:
    AmberTest();

private Q_SLOTS:
    void rawTransactionBenchmarkTest();
    void precreatedTransactionBenchmarkTest();
};

const amber::model::ValueT colorIncreaseStep = 0x100;

AmberTest::AmberTest()
{
}

stm::STML<stm::Unit> increaseColor(const amber::model::Scalar& scalar)
{
    using namespace amber::model;

    stm::STML<stm::Unit> increase
            = stm::modifyTVar<ValueT>(
                scalar.value,
                [](ValueT value) { return value + colorIncreaseStep; });

    stm::STML<stm::Unit> tryIncrease
            = stm::whenTVar<ValueT, stm::Unit>(scalar.value, isValidColor, increase);

    return stm::whenTVar<ScalarType, stm::Unit>(scalar.subtype, isColorScalarType, tryIncrease);
}

//void AmberTest::compositeTest()
//{
//    using namespace amber::model;

//    stm::Context ctx;

//    const ValueT initialColor = 0x00;
//    const ValueT maxColor = 0x0000ff00;

//    Scalar sky      = mkColorScalar(ctx, "sky", initialColor);

//    Scalar oxygen   = mkItemScalar(ctx, "oxygen");
//    Scalar nitrogen = mkItemScalar(ctx, "nitrogen");
//    Scalar water    = mkItemScalar(ctx, "water");

//    Scalar soil     = mkColorScalar(ctx, "soil", 0x66ffff00);
//    Scalar stones   = mkColorScalar(ctx, "stones", 0x66ffff00);
//    Scalar grass    = mkColorScalar(ctx, "grass", 0x66ffff00);

//    Composite air = mkPercentageComposite(ctx, "air",
//                { mkPercent(oxygen,   24),
//                  mkPercent(nitrogen, 72),
//                  mkPercent(water,    4) });

//    Composite ground = mkPercentageComposite(ctx, "ground",
//                { mkPercent(soil,   60),
//                  mkPercent(stones, 35),
//                  mkPercent(grass,  5) });

//    Composite world = mkStructuralComposite(ctx, "World 1", { sky, air, ground });

//    bool maxColorReached = false;
//    while (!maxColorReached)
//    {
//        stm::atomically(ctx, increaseColor(sky));
//        ValueT color = stm::readTVarIO(ctx, sky.value);
//        maxColorReached = color >= maxColor;
//    }

//    ValueT result = stm::readTVarIO(ctx, sky.value);
//    QCOMPARE(result, maxColor);
//}

void AmberTest::rawTransactionBenchmarkTest()
{
    using namespace amber::model;

    const ValueT initialColor = 0x00;
    const ValueT maxColor = 0x0000ff00;

    stm::Context ctx;

    Scalar sky = mkColorScalar(ctx, "sky", initialColor);

    // Result: 74.0 msecs
    QBENCHMARK {
        stm::atomically(ctx, stm::writeTVar(sky.value, initialColor));

        bool maxColorReached = false;
        while (!maxColorReached)
        {
            stm::atomically(ctx, increaseColor(sky));
            ValueT color = stm::readTVarIO(ctx, sky.value);
            maxColorReached = color >= maxColor;
        }
    }

    ValueT result = stm::readTVarIO(ctx, sky.value);
    QCOMPARE(result, maxColor);
}

void AmberTest::precreatedTransactionBenchmarkTest()
{
    using namespace amber::model;

    const ValueT initialColor = 0x00;
    const ValueT maxColor = 0x0000ff00;

    stm::Context ctx;

    Scalar sky = mkColorScalar(ctx, "sky", initialColor);
    auto increaseColorTrans = increaseColor(sky);

    // Result: 53.7 msecs
    QBENCHMARK {
        stm::atomically(ctx, stm::writeTVar(sky.value, initialColor));

        bool maxColorReached = false;
        while (!maxColorReached)
        {
            stm::atomically(ctx, increaseColorTrans);
            ValueT color = stm::readTVarIO(ctx, sky.value);
            maxColorReached = color >= maxColor;
        }
    }

    ValueT result = stm::readTVarIO(ctx, sky.value);
    QCOMPARE(result, maxColor);
}

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


QTEST_APPLESS_MAIN(AmberTest)

#include "tst_ambertest.moc"
