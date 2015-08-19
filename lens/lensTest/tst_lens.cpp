#include <QString>
#include <QtTest>

#include "../identity.h"
#include "../lenses.h"
#include "../fold.h"
#include "../combinators.h"

#include "common.h"
#include "address.h"
#include "person.h"

#include "struct_lenses.h"


using namespace sample;

class LensTest : public QObject
{
    Q_OBJECT

public:
    LensTest();

    Person getPerson() const;

private Q_SLOTS:

    void toCombinatorTest();
    void toVector1CombinatorTest();

    void setValueImplicitLensTest();
    void modifyValueOutlineLensTest();
    void modifyValueInlineLensTest();
};

LensTest::LensTest()
{
}

Person LensTest::getPerson() const
{
    Address address;
    address.city = "New York";
    address.street = "Brooklin";
    address.house = 20;
    address.flat = 2;

    Person person;
    person.name = "Paul";
    person.surname = "Jonson";
    person.age = 29;
    person.address = address;

    Car car1 = {"x555xx", "Ford Focus", 0};
    Car car2 = {"y555yy", "Toyota Corolla", 10000};

    person.cars = {car1, car2};

    return person;
}

void LensTest::toCombinatorTest()
{
    auto prx = addressL() to houseL();

    // TODO: add evalLens() for ToRProxy.
    Person newPerson = evalLens(prx(), getPerson(), set(100));

    QVERIFY(newPerson.address.house == 100);
}

void LensTest::toVector1CombinatorTest()
{
    Car car1 = {"x555xx", "Ford Focus", 0};
    Car car2 = {"y555yy", "Toyota Corolla", 10000};

    std::vector<Car> cars;
    cars = {car1, car2};

    auto fC = foldedC<Car>();

    auto zoomer = zoom_Fold_(fC, modelL());
    //FoldStack<std::vector<Car>, Car, std::string> zoomer2 = zoomer;
    auto result = toVectorOf(zoomer, cars);

    QVERIFY(result.size() == 2);
    QVERIFY(result[0] == "Ford Focus");
    QVERIFY(result[1] == "Toyota Corolla");
}

void LensTest::setValueImplicitLensTest()
{
    auto zoomer = zoom(addressL(), houseL());

    Person newPerson = evalLens(zoomer, getPerson(), set(100));

    QVERIFY(newPerson.address.house == 100);
}

void LensTest::modifyValueOutlineLensTest()
{
    auto zoomer = zoom(addressL(), houseL());
    std::function<int(int)> modifier = [](int old) { return old + 6; };

    Person newPerson = evalLens(zoomer, getPerson(), modifier);

    QVERIFY(newPerson.address.house == 26);
}

void LensTest::modifyValueInlineLensTest()
{
    auto zoomer = zoom(addressL(), houseL());

    Person newPerson = evalLens(zoomer, getPerson(), modify(int, _value + 6));

    QVERIFY(newPerson.address.house == 26);
}

QTEST_APPLESS_MAIN(LensTest)

#include "tst_lens.moc"
