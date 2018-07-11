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
    amber::model::Composite composite;

    amber::model::Components cs;
    composite.components = stm::newTVarIO(ctx, cs);
}

QTEST_APPLESS_MAIN(AmberTest)

#include "tst_ambertest.moc"
