#include "shadowsview.h"
#include "ui_shadowsview.h"

#include "shadows.h"

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
    shadows::goNorth(m_amber);
    updateUI();
}

void ShadowsView::updateUI()
{
    //todo
}
