#include <QString>
#include <QtTest>

#include "../identity.h"
#include "../lenses.h"
#include "../fold.h"
#include "../combinators.h"
#include "../bind.h"

#include "common.h"
#include "address.h"
#include "person.h"
#include "account.h"

#include "struct_lenses.h"


using namespace sample;

class LensTest : public QObject
{
    Q_OBJECT

public:
    LensTest();

    Address getAddress() const;
    Person getPerson() const;
    Account getAccount() const;

private Q_SLOTS:


    void genSetCombinatorTest();


    void toCombinatorTest();
    void toVectorCombinatorTest();
    void toListCombinatorTest();
    void overCombinatorTest();
    void setCombinatorTest();

    void setValueImplicitLensTest();
    void modifyValueOutlineLensTest();
    void modifyValueInlineLensTest();
};

LensTest::LensTest()
{
}

Address LensTest::getAddress() const
{
    Address address;
    address.city = "New York";
    address.street = "Brooklin";
    address.house = 20;
    address.flat = 2;
    return address;
}

Person LensTest::getPerson() const
{
    Car car1 = {"x555xx", "Ford Focus", 0};
    Car car2 = {"y555yy", "Toyota Corolla", 10000};

    Person person;
    person.name = "Paul";
    person.surname = "Jonson";
    person.age = 29;
    person.address = getAddress();
    person.cars = {car1, car2};
    return person;
}

Account LensTest::getAccount() const
{
    Account account;
    account.person = getPerson();
    account.login = "admin";
    account.password = "admin";
    return account;
}

void LensTest::genSetCombinatorTest()
{
    auto zoomer1 = LensStack2<Lens<Account, Person>>(personL());

    auto zoomer2 = LensStack3<Lens<Account, Person>>(personL());

    //auto zoomerX = LensStack3(personL());  // No way... Poor type inference


    auto zoomer3 = LensStack3<Lens<Account, Person>, Lens<Person, Address>>(personL(), addressL());
    auto zoomer4 = LensStack3<Lens<Account, Person>, Lens<Person, Address>, Lens<Address, int>>(personL(), addressL(), houseL());


    auto zoomer5_1 = bind<Account, Person, Address, int>(personL(), addressL(), houseL());
    auto zoomer5_2 = bind<Account, Person, Address>(personL(), addressL());
    auto zoomer5_3 = bind(personL(), addressL());
    auto zoomer5_4 = bind(personL(), addressL(), houseL());


    //auto zoomer = zoomV(personL(), addressL(), houseL());

    //Person newPerson = set(zoomer, getPerson(), 100);

    //QVERIFY(newPerson.address.house == 100);
}



void LensTest::toCombinatorTest()
{
    auto prx = addressL() to houseL();

    // TODO: add evalLens() for ToRProxy.
    Person newPerson = evalLens(prx(), getPerson(), set(100));

    QVERIFY(newPerson.address.house == 100);
}

void LensTest::toVectorCombinatorTest()
{
    Car car1 = {"x555xx", "Ford Focus", 0};
    Car car2 = {"y555yy", "Toyota Corolla", 10000};

    std::vector<Car> cars;
    cars = {car1, car2};

    auto fC = foldedC<Car>();

    auto zoomer = zoom_Fold_(fC, modelL());
    //FoldStack<std::vector<Car>, Car, std::string> zoomer2 = zoomer;
    std::vector<std::string> result = toVectorOf(zoomer, cars);

    QVERIFY(result.size() == 2);
    QVERIFY(result[0] == "Ford Focus");
    QVERIFY(result[1] == "Toyota Corolla");
}

void LensTest::toListCombinatorTest()
{
    Car car1 = {"x555xx", "Ford Focus", 0};
    Car car2 = {"y555yy", "Toyota Corolla", 10000};

    std::vector<Car> cars;
    cars = {car1, car2};

    auto fC = foldedC<Car>();

    auto zoomer = zoom_Fold_(fC, modelL());
    std::list<std::string> result = toListOf(zoomer, cars);

    QVERIFY(result.size() == 2);
    QVERIFY(result.front() == "Ford Focus");
    QVERIFY(result.back() == "Toyota Corolla");
}

void LensTest::overCombinatorTest()
{
    auto zoomer = zoom(addressL(), houseL());

    std::function<int(int)> modifier = [](int old) { return old + 6; };

    Person newPerson = over(zoomer, getPerson(), modifier);

    QVERIFY(newPerson.address.house == 26);
}

void LensTest::setCombinatorTest()
{
    auto zoomer = zoom(addressL(), houseL());

    Person newPerson = set(zoomer, getPerson(), 100);

    QVERIFY(newPerson.address.house == 100);
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
