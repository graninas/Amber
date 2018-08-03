#ifndef SHADOWSVIEW_H
#define SHADOWSVIEW_H

#include <QMainWindow>

#include <amber.h>
#include <stm/stm.h>

namespace Ui {
class ShadowsView;
}

class ShadowsView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShadowsView(QWidget *parent = 0);
    ~ShadowsView();

public slots:

private slots:
    void on_CreateItem_clicked();

private:
    Ui::ShadowsView *ui;

    stm::Context _ctx;
    amber::model::Composite _universe;
};

#endif // SHADOWSVIEW_H
