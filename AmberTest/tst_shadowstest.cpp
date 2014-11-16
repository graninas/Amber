#include <QString>
#include <QtTest>

class ShadowsTest : public QObject
{
    Q_OBJECT

public:
    ShadowsTest();

private Q_SLOTS:
    void goDirection();
};

ShadowsTest::ShadowsTest()
{
}

void ShadowsTest::goDirection()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ShadowsTest)

#include "tst_shadowstest.moc"
