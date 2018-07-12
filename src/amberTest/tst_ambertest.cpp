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
    void compositeTest();
};

AmberTest::AmberTest()
{
}

void AmberTest::compositeTest()
{
    stm::Context ctx;

    amber::model::IScalar sky      = amber::model::mkIScalar(ctx, "sky", 0x66ffff00);
    amber::model::IScalar oxygen   = amber::model::mkIScalar(ctx, "oxygen", 24);
    amber::model::IScalar nitrogen = amber::model::mkIScalar(ctx, "nitrogen", 72);
    amber::model::IScalar water    = amber::model::mkIScalar(ctx, "water", 4);

    amber::model::Percentage air = amber::model::mkPercentage(ctx, "air", { oxygen, nitrogen, water });

    amber::model::Composite world = amber::model::mkComposite(ctx, "World 1", { sky, air });
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
