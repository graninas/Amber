#include <QString>
#include <QtTest>

class AmberTest : public QObject
{
    Q_OBJECT

public:
    AmberTest();

private Q_SLOTS:
    void testCase1();
};

AmberTest::AmberTest()
{
}

void AmberTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(AmberTest)

#include "tst_ambertest.moc"
