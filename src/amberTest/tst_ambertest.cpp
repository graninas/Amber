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

    void rawLongSTMLBindBenchmarkTest();
    void precreatedLongSTMLBindBenchmarkTest();

    void rawLongScalarSTMLBindBenchmarkTest();
    void precreatedLongScalarSTMLBindBenchmarkTest();
};

const amber::model::Value colorIncreaseStep = 0x100;
const amber::model::Value initialColor = 0x00;
const amber::model::Value maxColor = 0x0000ff00;

const int maxBindChainLength = 30;
const int maxScalarBindChainLength = 30;

using ScalarTVar = stm::TVar<amber::model::Scalar>;


AmberTest::AmberTest()
{
}

stm::STML<amber::model::MaybeValue>
tryIncreaseColor(const amber::model::Scalar& scalar)
{
    using namespace amber::model;

    return stm::tryModifyTVar<Value>(
                scalar.value,
                [](Value value)
                {
                    Value newColor = value + colorIncreaseStep;
                    return isValidColor(newColor) && newColor <= maxColor
                            ? std::make_optional<Value>(newColor)
                            : std::nullopt;
                });
}

stm::STML<amber::model::MaybeValue>
tryIncreaseColorIfColorScalar(const amber::model::Scalar& scalar)
{
    using namespace amber::model;

    stm::STML<MaybeValue> tryIncreaseColorTrans = tryIncreaseColor(scalar);
    return stm::tryTVar<ScalarType, Value>(
                scalar.subtype,
                [](ScalarType subtype) { return subtype == ScalarType::Color; },
                tryIncreaseColorTrans);
}

stm::STML<amber::model::MaybeValue> tryIncreaseComponentColor(
        const std::string& name,
        const amber::model::Composite& composite)
{
    using namespace amber::model;

    return stm::bindOptional<Component, Value>(
        findComponent(name, composite),
        [](const Component& component)
        {
            return stm::bindOptional<Scalar, Value>(
                findScalar(ScalarType::Color, component),
                [](const Scalar& scalar)
                {
                    return tryIncreaseColor(scalar);
                });
        }
    );
}

stm::STML<amber::model::MaybeValue> tryDecreaseComponentPercent(
        const std::string& name,
        const amber::model::Composite& composite)
{
    using namespace amber::model;

    return stm::bindOptional<PercentComponent, Value>(
        findPercentComponent(name, composite),
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
    using namespace amber::model;

    auto trans = tryIncreaseColorIfColorScalar(sky);
    bool success = true;
    while (success)
    {
        MaybeValue skyColor = stm::atomically(ctx, trans);
        success = skyColor.has_value();
    }
}

void airPercentageWorker(stm::Context& ctx, const amber::model::Composite& air)
{
    using namespace amber::model;

    stm::STML<MaybeValue> trans = tryDecreaseComponentPercent("nitrogen", air);
    bool success = true;
    while (success)
    {
        MaybeValue nitrogenPercent = stm::atomically(ctx, trans);
        success = nitrogenPercent.has_value() && nitrogenPercent.value() <= 0;
    }
}

void airColorWorker(stm::Context& ctx, const amber::model::Composite& air)
{
    using namespace amber::model;

    stm::STML<MaybeValue> trans = tryIncreaseComponentColor("nitrogen", air);
    bool success = true;
    while (success)
    {
        MaybeValue nitrogenColor = stm::atomically(ctx, trans);
        success = nitrogenColor.has_value();
    }
}

void AmberTest::rawTransactionBenchmarkTest()
{
    using namespace amber::model;

    stm::Context ctx;

    Scalar sky = mkColorScalar(ctx, "sky", initialColor);

    bool success = true;

    // Result: 23.0 msecs
    QBENCHMARK {
        while (success)
        {
            auto mbNewColor = stm::atomically(ctx, tryIncreaseColorIfColorScalar(sky));
            success = mbNewColor.has_value();
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

    auto trans = tryIncreaseColorIfColorScalar(sky);
    bool success = true;

    // Result: 12.0 msecs
    QBENCHMARK {
        while (success)
        {
            auto mbNewColor = stm::atomically(ctx, trans);
            success = mbNewColor.has_value();
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

    // Result: 110.0 msecs
    QBENCHMARK {
        std::thread skyColorThread(skyColorWorker, std::ref(ctx), sky);
        std::thread airPercentageThread(airPercentageWorker, std::ref(ctx), air);
        std::thread airColorThread(airColorWorker, std::ref(ctx), air);

        skyColorThread.join();
        airPercentageThread.join();
        airColorThread.join();
    }
}

stm::STML<int> increaseTimes(const stm::TVar<int>& tvar, int times)
{
    if (times > 0)
    {
        return stm::sequence<stm::Unit, int>(
                    stm::modifyTVar<int>(tvar, [](int val) { return val + 1; }),
                    increaseTimes(tvar, times - 1));
    }
    else
    {
        return stm::readTVar(tvar);
    }
}

stm::STML<amber::model::Value>
increaseScalarTimes(const ScalarTVar& tvar, int times)
{
    using namespace amber::model;

    if (times > 0)
    {
        return stm::sequence<stm::Unit, Value>(
                    stm::withTVar<Scalar, stm::Unit>(
                        tvar,
                        [](const Scalar& scalar)
                        {
                            return stm::modifyTVar<Value>(scalar.value, [](Value val) { return val + 1; });
                        }),
                    increaseScalarTimes(tvar, times - 1));
    }
    else
    {
        return stm::withTVar<Scalar, Value>(
                    tvar,
                    [](const Scalar& scalar)
                    {
                        return stm::readTVar<Value>(scalar.value);
                    });
    }
}

void AmberTest::rawLongSTMLBindBenchmarkTest()
{
    stm::Context ctx;

    stm::TVar<int> tvar = stm::newTVarIO(ctx, 0);
    int result = 0;

    QBENCHMARK {
        result = stm::atomically(ctx, increaseTimes(tvar, maxBindChainLength));
    }

    QVERIFY(result == maxBindChainLength);
}

void AmberTest::precreatedLongSTMLBindBenchmarkTest()
{
    stm::Context ctx;

    stm::TVar<int> tvar = stm::newTVarIO(ctx, 0);
    auto trans = increaseTimes(tvar, maxBindChainLength);
    int result = 0;

    QBENCHMARK {
        result = stm::atomically(ctx, trans);
    }

    QVERIFY(result == maxBindChainLength);
}



void AmberTest::rawLongScalarSTMLBindBenchmarkTest()
{
    using namespace amber::model;

    stm::Context ctx;

    Scalar scalar = mkScalar(ctx, "Some Scalar", 0, ScalarType::Value);
    ScalarTVar scalarTVar = stm::newTVarIO(ctx, scalar);

    int result = 0;

    QBENCHMARK {
        result = stm::atomically(ctx, increaseScalarTimes(scalarTVar, maxScalarBindChainLength));
    }

    QVERIFY(result == maxScalarBindChainLength);
}

void AmberTest::precreatedLongScalarSTMLBindBenchmarkTest()
{
    using namespace amber::model;

    stm::Context ctx;

    Scalar scalar = mkScalar(ctx, "Some Scalar", 0, ScalarType::Value);
    ScalarTVar scalarTVar = stm::newTVarIO(ctx, scalar);

    auto trans = increaseScalarTimes(scalarTVar, maxScalarBindChainLength);
    int result = 0;

    QBENCHMARK {
        result = stm::atomically(ctx, trans);
    }

    QVERIFY(result == maxScalarBindChainLength);
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
