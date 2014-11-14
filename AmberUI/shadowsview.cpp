#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "shadows.h"
#include "magic.h"

#include "common.h"
#include "assets.h"

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

    amber::AmberTask task = [](const amber::Amber& amber) -> amber::Amber
    {
        auto action1Res = magic::anyway(shadows::goNorth, magic::wrap(amber));
        auto action2Res = magic::anyway(shadows::tickDay, action1Res);
        return action2Res.amber;
    };

    amber::changeAmber(task, m_amber);
    updateUI();
}

void ShadowsView::updateUI()
{
    ui->l_Time->setText(QString::number(m_amber.hoursElapsed));
}
