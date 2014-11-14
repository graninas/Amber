#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "shadows.h"
#include "magic.h"

#include "common.h"

ShadowsView::ShadowsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowsView)
{
    ui->setupUi(this);
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

   auto newAmber = amber::changeAmber(task, m_amber);

   m_amber = newAmber;


    updateUI();
}

void ShadowsView::updateUI()
{
    //todo
}
