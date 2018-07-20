#include <QString>
#include <QtTest>

#include <stm.h>
#include <stm_optional.h>
#include <thread>

#include "../amber/model/transactions.h"
#include "../amber/model/helpers.h"
#include "../amber/model/model.h"

class AmberTest : public QObject
{
    Q_OBJECT

public:
    AmberTest();

private Q_SLOTS:
    void rawTransactionBenchmarkTest();
    void precreatedTransactionBenchmarkTest();

    void worldInteractionBenchmarkTest();
};

const amber::model::Value colorIncreaseStep = 0x100;
const amber::model::Value initialColor = 0x00;
const amber::model::Value maxColor = 0x0000ff00;

AmberTest::AmberTest()
{
}

stm::STML<stm::Unit> increaseColor(const amber::model::Scalar& scalar)
{
    using namespace amber::model;

    stm::STML<stm::Unit> increase
            = stm::modifyTVar<Value>(
                scalar.value,
                [](Value value) { return value + colorIncreaseStep; });

    stm::STML<stm::Unit> tryIncrease
            = stm::whenTVar<Value, stm::Unit>(scalar.value, isValidColor, increase);

    return stm::whenTVar<ScalarType, stm::Unit>(scalar.subtype, isColorScalarType, tryIncrease);
}

//stm::STML<stm::Unit> increaseColor(const amber::model::Scalar& scalar)
//{
//    using namespace amber::model;

//    stm::STML<stm::Unit> increase
//            = stm::modifyTVar<Value>(
//                scalar.value,
//                [](Value value) { return value + colorIncreaseStep; });

//    stm::STML<stm::Unit> tryIncrease
//            = stm::whenTVar<Value, stm::Unit>(scalar.value, isValidColor, increase);

//    return stm::whenTVar<ScalarType, stm::Unit>(scalar.subtype, isColorScalarType, tryIncrease);
//}

stm::STML<amber::model::MaybeValue> tryDecreaseComponentPercent(
        const std::string& name,
        const amber::model::Composite& composite)
{
    using namespace amber::model;

    return stm::withOptional<PercentComponent, MaybeValue>(
        findPercentComponent(name, composite),
        stm::pure<MaybeValue>(std::nullopt),
        [](const PercentComponent& component)
        {
            return stm::tryModifyTVar<Value>(
                        component.percent,
                        [](Value value)
            {
                return value <= 0
                        ? std::nullopt
                        : std::make_optional<Value>(value - 1);
            });
        }
    );
}

void skyColorWorker(stm::Context& ctx, const amber::model::Scalar& sky)
{
    auto increaseColorTrans = increaseColor(sky);
    bool maxColorReached = false;
    while (!maxColorReached)
    {
        stm::atomically(ctx, increaseColorTrans);
        amber::model::Value color = stm::readTVarIO(ctx, sky.value);
        maxColorReached = color >= maxColor;
    }
}

void airPercentageWorker(stm::Context& ctx, const amber::model::Composite& air)
{
    using namespace amber::model;

    stm::STML<MaybeValue> tryDecreaseNitrogenPercentTrans = tryDecreaseComponentPercent("nitrogen", air);
    bool minNitrogenReached = false;
    while (!minNitrogenReached)
    {
        MaybeValue nitrogenPercent = stm::atomically(ctx, tryDecreaseNitrogenPercentTrans);
        minNitrogenReached = !nitrogenPercent.has_value() || nitrogenPercent.value() <= 0;
    }
}

void airColorWorker(stm::Context& ctx, const amber::model::Composite& air)
{
//    auto increaseColorTrans = increaseColor(sky);
//    bool maxColorReached = false;
//    while (!maxColorReached)
//    {
//        stm::atomically(ctx, increaseColorTrans);
//        amber::model::Value color = stm::readTVarIO(ctx, sky.value);
//        maxColorReached = color >= maxColor;
//    }
}


//void AmberTest::compositeTest()
//{
//    using namespace amber::model;

//    stm::Context ctx;

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

//}

void AmberTest::rawTransactionBenchmarkTest()
{
    using namespace amber::model;

    stm::Context ctx;

    Scalar sky = mkColorScalar(ctx, "sky", initialColor);

    // Result: 75.0 msecs
    QBENCHMARK {
        bool maxColorReached = false;
        while (!maxColorReached)
        {
            stm::atomically(ctx, increaseColor(sky));
            Value color = stm::readTVarIO(ctx, sky.value);
            maxColorReached = color >= maxColor;
        }
    }

    Value result = stm::readTVarIO(ctx, sky.value);
    QCOMPARE(result, maxColor);
}

void AmberTest::precreatedTransactionBenchmarkTest()
{
    using namespace amber::model;

    stm::Context ctx;

    Scalar sky = mkColorScalar(ctx, "sky", initialColor);
    auto increaseColorTrans = increaseColor(sky);

    // Result: 50.0 msecs
    QBENCHMARK {
        bool maxColorReached = false;
        while (!maxColorReached)
        {
            stm::atomically(ctx, increaseColorTrans);
            Value color = stm::readTVarIO(ctx, sky.value);
            maxColorReached = color >= maxColor;
        }
    }

    Value result = stm::readTVarIO(ctx, sky.value);
    QCOMPARE(result, maxColor);
}

void AmberTest::worldInteractionBenchmarkTest()
{
    using namespace amber::model;

    stm::Context ctx;

    Scalar sky      = mkColorScalar(ctx, "sky", initialColor);

    Scalar oxygen   = mkColorScalar(ctx, "oxygen",   initialColor);
    Scalar nitrogen = mkColorScalar(ctx, "nitrogen", initialColor);
    Scalar water    = mkColorScalar(ctx, "water",    initialColor);

    Composite air = mkPercentageComposite(ctx, "air",
                { {"oxygen",   {oxygen,   24}},
                  {"nitrogen", {nitrogen, 72}},
                  {"water",    {water,    4 }} });

    QBENCHMARK {
        std::thread skyColorThread(skyColorWorker, std::ref(ctx), sky);
        std::thread airPercentageThread(airPercentageWorker, std::ref(ctx), air);
        std::thread airColorThread(airColorWorker, std::ref(ctx), air);

        skyColorThread.join();
        airPercentageThread.join();
        airColorThread.join();
    }
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
