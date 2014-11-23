#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "ambermechanics.h"
#include "magic.h"

#include "common.h"
#include "naming.h"

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

    updateUI();
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
    amber::AmberTask combinedTask = [](const amber::Amber& amber)
    {
        auto action1Res = magic::anyway(amber::shadowStormsInfluence, magic::wrap(amber));
        auto action2Res = magic::anyway(amber::shadowStabilization, action1Res);
        auto action3Res = magic::anyway(amber::tickWorldTime, action2Res);
        return action3Res.amber;
    };

    changeAmber(combinedTask);
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

void ShadowsView::updateUI()
{
    amber::Amber amber = readAmber();

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
}

amber::Amber ShadowsView::readAmber() const
{
    m_amberChangeGuard.lock();
    amber::Amber amber = m_amber;
    m_amberChangeGuard.unlock();
    return amber;
}

// Presentation tip: C++ hasn't atomic methods.
void ShadowsView::changeAmber(const amber::AmberTask& task)
{
    m_amberChangeGuard.lock();
    m_amber = task(m_amber);
    m_amberChangeGuard.unlock();
    updateUI();
}
