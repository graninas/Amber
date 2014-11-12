#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "amber.h"
#include "shadows.h"

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
    auto res = amber::changeAmber([](const amber::Amber& amber)
    {
        //auto action1Res = anyway(shadows::goNorth, wrap(m_amber));
        //auto action2Res = anyway(shadows::tickDay, action1Res);
        //return action2Res;
        return amber;
    }, m_amber);

    // todo: res

    updateUI();
}

void ShadowsView::updateUI()
{
    //todo
}
