#include "shadowsview.h"
#include "ui_shadowsview.h"

ShadowsView::ShadowsView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowsView),
    _ctx()
{
    ui->setupUi(this);

    _universe = amber::model::mkStructuralComposite(_ctx, "Universe", {});
    auto composite = std::get<amber::model::StructuralComposite>(_universe.composite);
    QTreeWidgetItem *topItem = ui->universeTree->topLevelItem(0);
    Q_ASSERT(topItem != nullptr);
    Q_ASSERT(topItem->text(0) == "World");
    topItem->setData(0, Qt::ToolTipRole, composite.components.id);
}

ShadowsView::~ShadowsView()
{
    delete ui;
}

void ShadowsView::on_CreateItem_clicked()
{

}
