#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "shadowstructure.h"
#include "shadows.h"
#include "magic.h"

#include "common.h"
#include "assets.h"

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

void ShadowsView::directionAmber()
{
    m_amber.direction = amber::Pole::Amber;
}

void ShadowsView::directionChaos()
{
    m_amber.direction = amber::Pole::Chaos;
}

void ShadowsView::updateUI()
{
    ui->l_time->setText(QString::number(m_amber.hoursElapsed));
    ui->l_polePosition->setText(QString::number(m_amber.worldPolePosition));
    ui->hs_polePosition->setValue(worldPolePositionToSliderValue(m_amber.worldPolePosition));
}
