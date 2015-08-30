#include <QString>
#include <QtTest>

#include <monads.h>

class monadTest : public QObject
{
    Q_OBJECT

public:
    monadTest();

private Q_SLOTS:
    void testMonad();
};

monadTest::monadTest()
{
}

void monadTest::testMonad()
{
    monad::MaybeBool mbBool;

    mbBool.data = true;

    QVERIFY(mbBool.data);
}

QTEST_APPLESS_MAIN(monadTest)

#include "tst_monadtest.moc"
