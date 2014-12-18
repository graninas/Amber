#ifndef LENS_H
#define LENS_H

namespace experimental
{

using namespace lenses;

struct InnerStruct
{
    int i;
};

struct Test
{
    InnerStruct inner;
    std::string s;
};

const std::function<int(int)> increaseI = [](int i)
{
    return ++i;
};

std::function<std::string(std::string)> replaceString(const std::string& s)
{
    return [=](const std::string&)
    {
        return s;
    };
}

// TODO: create a macro for this.
Lens<InnerStruct, int> intIL()
{
    return lens<InnerStruct, int>
            ( [](const InnerStruct& inner) { return inner.i; }
            , [](const InnerStruct& inner, int i) {
                InnerStruct newInnerStruct = inner;
                newInnerStruct.i = i;
                return newInnerStruct;
            }
        );
}

Lens<Test, std::string> stringL()
{
    return lens<Test, std::string>
            ( [](const Test& t) { return t.s; }
            , [](const Test& t, const std::string& s) {
                Test newTest = t;
                newTest.s = s;
                return newTest;
            }
    );
}

Lens<Test, InnerStruct> innerL()
{
    return lens<Test, InnerStruct>
            ( [](const Test& t) { return t.inner; }
            , [](const Test& t, const InnerStruct& inner) {
                Test newTest = t;
                newTest.inner = inner;
                return newTest;
            }
    );
}

Test testLens(const Test& test)
{
    LensStack<Test, InnerStruct, int> lensStack1
       = zoom(innerL(), intIL());

    LensStack<Test, std::string> lensStack2
       = zoom(stringL());

    Test newTest1 = evalLens(lensStack1, test, increaseI);
    Test newTest2 = evalLens(lensStack2, newTest1, replaceString("bla-bla"));

    return newTest2;
}

struct C {
    int intC;
    std::string stringC;
};

struct B {
    C c;
};

struct A {
    B b;
};

/*
// The Law of Demeter violation!
void changeC(A& a) {
    a.b.c.intC = 20;
    a.b.c.stringC = "Hello, World!";
}

A changeC(const A& oldA)
{
    C newC = oldA.b.c;
    newC.intC = 20;
    newC.stringC = "Hello, world!";

    B newB = oldA.b;
    newB.c = newC;

    A newA = oldA;
    newA.b = newB;
    return newA;
}
*/


Lens<A, B> aToBLensDesugared() {
    return lens<A, B>
            ( [](const A& a) { return a.b; }

            , [](const A& a, const B& b) {
                A newA = a;
                newA.b = b;
                return newA;
            });
}


Lens<A, B> aToBLens() {
    return lens<A, B> ( GETTER(A, b)
                      , SETTER(A, B, b));
}

Lens<B, C> bToCLens() {
    return lens<B, C> ( GETTER(B, c)
                      , SETTER(B, C, c));
}

std::function<C(C)> modifyC = [](const C& c) {
    return C { c.intC + 20, "Hello, World!" };
};

A changeC(const A &oldA) {
    LensStack<A, B, C> intCStack = zoom(aToBLensDesugared(), bToCLens());
    A newA = evalLens(intCStack, oldA, modifyC);
    return newA;
}



} // namespace experimental

#endif // LENS_H
