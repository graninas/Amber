#include "amberview.h"
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
    topItem->setData(0, Qt::UserRole, TVarType::Components);
}

ShadowsView::~ShadowsView()
{
    delete ui;
}

void ShadowsView::on_CreateItem_clicked()
{
    auto current = ui->universeTree->currentItem();
    if (current == nullptr)
        return;

    bool ok;
    TVarType::TVarType t = current->data(0, Qt::UserRole).toInt(&ok);
    Q_ASSERT(ok);

    switch (t) {
        case TVarType::Components:
            ComponentsTVar tvar;
            tvar.id = current->data(0, Qt::ToolTipRole).toInt(&ok);
            Q_ASSERT(ok);

            auto child = addComponent(tvar,
                         ui->itemName->text(),
                         ui->itemType->currentText(),
                         ui->itemSubtype->currentText());
    case value:

        break;
    default:
        break;
    }
}
