#include "shadowsview.h"
#include "ui_shadowsview.h"

#include <amber.h>
#include <ambermechanics.h>
#include <naming.h>

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

void ShadowsView::evalAmberTask(const amber::AmberTask& task)
{
    amber::AmberTask combinedTask = [&task](const amber::Amber& amber)
    {
        auto action1Res = anyway(task, pure(amber));
        auto action2Res = anyway(amber::tickWorldTime, action1Res);
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
