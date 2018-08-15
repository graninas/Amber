#include "amberview.h"
#include "ui_amberview.h"

#include "ui_model.h"


using namespace amber::model;

AmberView::AmberView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AmberView),
    _ctx()
{
    ui->setupUi(this);

    _world = amber::assets::world1(_ctx);

    updateUI(_world);
}

AmberView::~AmberView()
{
    delete ui;
}

void AmberView::on_CreateItem_clicked()
{
    auto current = ui->universeTree->currentItem();
    if (current == nullptr)
        return;
}

void AmberView::updateUI(const amber::model::World& world)
{
    QTreeWidgetItem *root = new QTreeWidgetItem();
    root->setText(0, QString::fromStdString(world.name));
    ui->universeTree->addTopLevelItem(root);

//    topItem->setData(0, TVarIdRole, componentsTVar.id);
//    topItem->setData(0, TVarTypeRole, static_cast<int>(TVarType::Components));

}
