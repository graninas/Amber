#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "ambermechanics.h"
#include "magic.h"
#include "lenses.h"

#include "common.h"
#include "naming.h"

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
       = zoom<Test, InnerStruct, int>(innerL(), intIL());

    LensStack<Test, std::string> lensStack2
       = zoom<Test, std::string>(stringL());

    Test newTest1 = evalLens(lensStack1, test, increaseI);
    Test newTest2 = evalLens(lensStack2, newTest1, replaceString("bla-bla"));

    return newTest2;
}



} // namespace experimental

ShadowsView::ShadowsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowsView)
{
    m_amber = amber::defaultAmber();

    ui->setupUi(this);

    m_amberTimer = new QTimer(this);
    m_amberTimer->setSingleShot(false);
    m_amberTimer->setInterval(1000);
    QObject::connect(m_amberTimer, SIGNAL(timeout()), this, SLOT(tickOneAmberHour()));

    updateUI(m_amber);
}

ShadowsView::~ShadowsView()
{
    delete ui;
}

// This boilerplace can be removed by a macro.

void ShadowsView::goNorth()
{
    evalAmberTask(amber::goNorth);
}

void ShadowsView::goSouth()
{
    evalAmberTask(amber::goSouth);
}

void ShadowsView::goWest()
{
    evalAmberTask(amber::goWest);
}

void ShadowsView::goEast()
{
    evalAmberTask(amber::goEast);
}

void ShadowsView::goNorthEast()
{
    evalAmberTask(amber::goNorthEast);
}

void ShadowsView::goNorthWest()
{
    evalAmberTask(amber::goNorthWest);
}

void ShadowsView::goSouthEast()
{
    evalAmberTask(amber::goSouthEast);
}

void ShadowsView::goSouthWest()
{
    evalAmberTask(amber::goSouthWest);
}

void ShadowsView::tickOneAmberHour()
{
    changeAmber(amber::tickOneAmberHour);
}

void ShadowsView::switchAmberTimeTicking(bool ticking)
{
    Q_ASSERT(m_amberTimer != nullptr);
    Q_ASSERT(m_amberTimer->isActive() != ticking);

    if (ticking)
        m_amberTimer->start();
    else
        m_amberTimer->stop();
}

void ShadowsView::test()
{
    experimental::Test t { experimental::InnerStruct { 10 }, "" };
    experimental::Test newTest = experimental::testLens(t);
    Q_ASSERT(newTest.inner.i == 11);
    Q_ASSERT(newTest.s == "bla-bla");

    changeAmber(amber::sleep8hours);
}

void ShadowsView::evalAmberTask(const amber::AmberTask& task)
{
    // TODO: do something like frp.
    // Presentation tip: combinatorial pattern with a little combinatorial eDSL.
    amber::AmberTask combinedTask = [&task](const amber::Amber& amber)
    {
        auto action1Res = magic::anyway(task, magic::wrap(amber));
        auto action2Res = magic::anyway(amber::tickWorldTime, action1Res);
        return action2Res.amber;
    };

    changeAmber(combinedTask);
}

void ShadowsView::evaluateTasks(const std::list<amber::AmberTask>& tasks)
{
    m_amberChangeGuard.lock();
    amber::Amber currentAmber = m_amber;

    std::for_each(tasks.begin(), tasks.end(),
        [&currentAmber](const amber::AmberTask& task)
        {
            currentAmber = task(currentAmber);
        });

    m_amber = currentAmber;
    updateUI(m_amber);
    m_amberChangeGuard.unlock();
}

// Presentation tip: C++ hasn't atomic methods.
void ShadowsView::changeAmber(const amber::AmberTask& task)
{
    m_amberChangeGuard.lock();
    m_amber = task(m_amber);
    updateUI(m_amber);
    m_amberChangeGuard.unlock();
}


void ShadowsView::updateUI(const amber::Amber& amber)
{
    ui->l_time->setText(QString::number(amber.hoursElapsed));
    ui->l_area->setText(QString::fromStdString(naming::areaName(amber.nearestPlace.area)));
    ui->l_shadow->setText(QString::fromStdString(naming::shadowName(amber.nearestPlace.shadow)));

    ui->l_air->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Air)));
    ui->l_water->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Water)));
    ui->l_ground->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Ground)));
    ui->l_sky->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Sky)));
    ui->l_amberDistance->setText(QString::number(amber.playerShadowStructure.at(amber::Element::AmberDistance)));
    ui->l_chaosDistance->setText(QString::number(amber.playerShadowStructure.at(amber::Element::ChaosDistance)));
    ui->l_flora->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Flora)));
    ui->l_fauna->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Fauna)));

    ui->l_air_2->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Air)));
    ui->l_water_2->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Water)));
    ui->l_ground_2->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Ground)));
    ui->l_sky_2->setText(QString::number(amber.playerShadowStructure.at(amber::Element::Sky)));

    appendAmberLog(amber.log);
    ui->pte_amberLog->setPlainText(m_amberLog);
}

void ShadowsView::appendAmberLog(const amber::Log& log)
{
    m_amberLog.clear();
    std::string prev = "";
    for (auto s: log)
    {
        if (s == prev)
            continue;

        prev = s;
        m_amberLog.append(QString::fromStdString(s));
        m_amberLog.append("\n");
    }
}
