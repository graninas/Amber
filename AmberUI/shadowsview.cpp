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
    setupWorldPlacesModel(m_amber);

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
        auto action1Res = magic::anyway(amber::shadowStabilization, magic::wrap(amber));
        auto action2Res = magic::anyway(amber::tickWorldTime, action1Res);
        return action2Res.amber;
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
    amber::AmberTask combinedTask = [&task](const amber::Amber& amber)
    {
        auto action1Res = magic::anyway(task, magic::wrap(amber));
        auto action2Res = magic::anyway(amber::tickWorldTime, action1Res);
        return action2Res.amber;
    };

    changeAmber(combinedTask);
}

void ShadowsView::setupWorldPlacesModel(const amber::Amber& amber)
{
    /*
    QStringListModel model;
    Q_ASSERT(model.insertColumns(0, 10)); // This is a magic constant.
    Q_ASSERT(model.setHeaderData(0, Qt::Horizontal, QString("Area"), Qt::DisplayRole));
    Q_ASSERT(model.setHeaderData(1, Qt::Horizontal, QString("Shadow"), Qt::DisplayRole));

    std::for_each(amber.areas.begin(), amber.areas.end(),
                  [this, &model](const amber::Areas::value_type& areaDef)
    {
        Q_ASSERT(model.insertRow(0));
        QModelIndex idx = model.index(0, 0);
        Q_ASSERT(idx.isValid());
        Q_ASSERT(model.setData(idx, QString::fromStdString(areaDef.first)));

        const amber::Area& area = areaDef.second;
        std::for_each(area.shadows.begin(), area.shadows.end(),
                      [&model](const amber::Shadows::value_type& shadowDef)
        {
            QModelIndex idx = model.index(0, 1);
            Q_ASSERT(idx.isValid());
            Q_ASSERT(model.setData(idx, QString::fromStdString(shadowDef.first)));

            const amber::Shadow& shadow = shadowDef.second;
            int counter = 2;
            std::for_each(shadow.structure.begin(), shadow.structure.end(),
                          [&counter, &model](const amber::ShadowStructure::value_type& structDef)
            {
                Q_ASSERT(model.setHeaderData(counter,
                                                          Qt::Horizontal,
                                                          QString::fromStdString(naming::ElementName(structDef.first)),
                                                          Qt::DisplayPropertyRole));
                QModelIndex idx = model.index(0, counter);
                Q_ASSERT(idx.isValid());
                Q_ASSERT(model.setData(idx, QString::number(structDef.second)));
            });
        });
    });
    */

    QString model;

    std::for_each(amber.areas.begin(), amber.areas.end(),
                  [&model](const amber::Areas::value_type& areaDef)
    {
        QString row(QString::fromStdString(areaDef.first));
        row.append(":");

        const amber::Area& area = areaDef.second;
        std::for_each(area.shadows.begin(), area.shadows.end(),
                      [&row](const amber::Shadows::value_type& shadowDef)
        {
            row.append(QString::fromStdString(shadowDef.first));

            const amber::Shadow& shadow = shadowDef.second;
            std::for_each(shadow.structure.begin(), shadow.structure.end(),
                          [&row](const amber::ShadowStructure::value_type& structDef)
            {
                row.append("|");
                row.append(QString::fromStdString(naming::ElementName(structDef.first)));
                row.append(":");
                row.append(QString::number(structDef.second));
            });
        });

        model.append("\n\r");
        model.append(row);
    });

    ui->pte_worldPlaces->setPlainText(model);
}

void ShadowsView::updateUI()
{
    amber::Amber amber = readAmber();

    ui->l_time->setText(QString::number(amber.hoursElapsed));
    ui->l_area->setText(QString::fromStdString(naming::AreaName(amber.nearestPlace.area)));
    ui->l_shadow->setText(QString::fromStdString(naming::ShadowName(amber.nearestPlace.shadow)));

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
