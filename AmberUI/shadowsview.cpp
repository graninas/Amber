#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "shadowstructure.h"
#include "shadows.h"
#include "magic.h"
#include "shadowmechanics.h"

#include "amberpolearea.h"

#include "common.h"
#include "assets.h"
#include "naming.h"

namespace
{
int worldPolePositionToSliderValue(int polePos)
{
    return polePos;
}
}

ShadowsView::ShadowsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowsView)
{
    m_amber = amber::defaultAmber();

    ui->setupUi(this);
    setupWorldPlacesModel(m_amber);

    updateUI();
}

ShadowsView::~ShadowsView()
{
    delete ui;
}

void ShadowsView::goNorth()
{
    // TODO: do something like frp.
    amber::AmberTask task = [](const amber::Amber& amber) -> amber::Amber
    {
        auto action1Res = magic::anyway(shadows::goNorth, magic::wrap(amber));
        auto action2Res = magic::anyway(shadows::tickDay, action1Res);
        return action2Res.amber;
    };

    amber::changeAmber(task, m_amber);
    updateUI();
}

void ShadowsView::test()
{
    amber::Amber northMoved = shadows::updateCurrentShadow(m_amber, amber::Direction::North);
    amber::Amber southMoved = shadows::updateCurrentShadow(m_amber, amber::Direction::South);
    amber::Amber westMoved = shadows::updateCurrentShadow(m_amber, amber::Direction::West);
    amber::Amber eastMoved = shadows::updateCurrentShadow(m_amber, amber::Direction::East);

    amber::ShadowStructure s1 = amber::amberShadowStructure();

    magic::Value<amber::ShadowStructure> res = amber::safeElementChange(s1, amber::Element::Air, 100);
    //Q_ASSERT(magic::resultData(res) == s1.at(amber::Element::Air) + 1);

    //Q_ASSERT(northMoved.currentShadowStructure != m_amber.currentShadowStructure);
    //amber::ShadowStructure s1 = amber::amberShadowStructure();
    //amber::ShadowVariator v1 = amber::amberVariator();
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
    ui->l_time->setText(QString::number(m_amber.hoursElapsed));
    ui->l_area->setText(QString::fromStdString(naming::AreaName(m_amber.position.area)));
    ui->l_shadow->setText(QString::fromStdString(naming::ShadowName(m_amber.position.shadow)));

    ui->l_air->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::Air)));
    ui->l_water->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::Water)));
    ui->l_ground->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::Ground)));
    ui->l_sky->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::Sky)));
    ui->l_amberDistance->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::AmberDistance)));
    ui->l_chaosDistance->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::ChaosDistance)));
    ui->l_flora->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::Flora)));
    ui->l_fauna->setText(QString::number(m_amber.currentShadowStructure.at(amber::Element::Fauna)));
}
