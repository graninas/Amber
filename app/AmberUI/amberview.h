#ifndef AMBERVIEW_H
#define AMBERVIEW_H

#include <QMainWindow>

#include <amber.h>
#include <stm/stm.h>

namespace TVarType {
enum TVarType
{
    String,
    Components,
    PercentComponents,
    Component,
    Value,
    ScalarType
};
} // namespace TVarType

using ComponentsTVar = stm::TVar<amber::model::Components>;

namespace Ui {
class AmberView;
}

class AmberView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AmberView(QWidget *parent = 0);
    ~AmberView();

public slots:

private slots:
    void on_CreateItem_clicked();

private:
    Ui::AmberView *ui;

    stm::Context _ctx;
    amber::model::Composite _universe;
};

#endif // AMBERVIEW_H
