#ifndef SHADOWSVIEW_H
#define SHADOWSVIEW_H

#include <QMainWindow>

#include "amber.h"

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

    void goNorth();
    void directionAmber();
    void directionChaos();

private:
    Ui::ShadowsView *ui;

    amber::Amber m_amber;

    void updateUI();
};

#endif // SHADOWSVIEW_H
