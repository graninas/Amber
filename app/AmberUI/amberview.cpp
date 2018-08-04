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

    ui->colorScalarGB->hide();
    ui->itemScalarGB->hide();
    ui->percentageCompositeGB->hide();
    ui->structuralCompositeGB->hide();

    _universe = amber::model::mkStructuralComposite(_ctx, "Universe", {});
    auto composite = std::get<amber::model::StructuralComposite>(_universe.composite);
    QTreeWidgetItem *topItem = ui->universeTree->topLevelItem(0);
    Q_ASSERT(topItem != nullptr);
    Q_ASSERT(topItem->text(0) == "World");
    topItem->setData(0, Qt::ToolTipRole, composite.components.id);
    topItem->setData(0, Qt::UserRole, static_cast<int>(TVarType::Components));
}

AmberView::~AmberView()
{
    delete ui;
}

void AmberView::adjustItemCreationControls(int componentTypeInt)
{
    switch (static_cast<ComponentType>(componentTypeInt)) {
    case ComponentType::Scalar:

        break;
    case ComponentType::Composite:
        break;
    }
}

void AmberView::on_CreateItem_clicked()
{
    auto current = ui->universeTree->currentItem();
    if (current == nullptr)
        return;

    bool ok;
    auto t = static_cast<TVarType>(current->data(0, Qt::UserRole).toInt(&ok));
    Q_ASSERT(ok);

//    switch (t) {
//        case TVarType::Components:
//            ComponentsTVar tvar;
//            tvar.id = static_cast<stm::TVarId>(current->data(0, Qt::ToolTipRole).toInt(&ok));
//            Q_ASSERT(ok);

////            auto child = addComponent(tvar,
////                         ui->itemName->text(),
////                         ui->itemType->currentIndex(),
////                         ui->itemSubtype->currentIndex());

//    }
}
