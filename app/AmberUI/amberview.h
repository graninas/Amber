#ifndef AMBERVIEW_H
#define AMBERVIEW_H

#include <QMainWindow>

#include <amber.h>
#include <stm/stm.h>

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
    amber::model::World _world;

    void updateUI(const amber::model::World& world);
};

#endif // AMBERVIEW_H
