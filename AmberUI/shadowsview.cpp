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

// This boilerplace can be removed by a macro.

void ShadowsView::goNorth()
{
    evalAmberTask(shadows::goNorth);
}

void ShadowsView::goSouth()
{
    evalAmberTask(shadows::goSouth);
}

void ShadowsView::goWest()
{
    evalAmberTask(shadows::goWest);
}

void ShadowsView::goEast()
{
    evalAmberTask(shadows::goEast);
}

void ShadowsView::goNorthEast()
{
    evalAmberTask(shadows::goNorthEast);
}

void ShadowsView::goNorthWest()
{
    evalAmberTask(shadows::goNorthWest);
}

void ShadowsView::goSouthEast()
{
    evalAmberTask(shadows::goSouthEast);
}

void ShadowsView::goSouthWest()
{
    evalAmberTask(shadows::goSouthWest);
}

void ShadowsView::test()
{
    amber::ShadowStructure s1 = amber::amberShadowStructure();
    amber::SafeShadowStructure value = amber::safeWrap(s1);
    Q_ASSERT(value.data == s1);
    Q_ASSERT(value.result == magic::Result::Success);

    amber::SafeShadowStructure ss2 = amber::safeElementChange(s1, amber::Element::Air, 100);
    Q_ASSERT(ss2.result == magic::Result::Success);
    Q_ASSERT(ss2.data != s1);
}

void ShadowsView::evalAmberTask(const amber::AmberTask& task)
{
    // TODO: do something like frp.
    amber::AmberTask resultTask = [&task](const amber::Amber& amber) -> amber::Amber
    {
        auto action1Res = magic::anyway(task, magic::wrap(amber));
        auto action2Res = magic::anyway(shadows::tickDay, action1Res);
        return action2Res.amber;
    };

    amber::changeAmber(resultTask, m_amber);
    updateUI();
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
