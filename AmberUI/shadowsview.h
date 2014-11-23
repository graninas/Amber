#ifndef SHADOWSVIEW_H
#define SHADOWSVIEW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QTimer>
#include <mutex>

#include "amber.h"
#include "qambersurroundingstablemodel.h"

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

    // This boilerplace can be removed by a macro.
    void goNorth();
    void goSouth();
    void goWest();
    void goEast();
    void goNorthEast();
    void goNorthWest();
    void goSouthEast();
    void goSouthWest();
    void tickOneAmberHour();

    void switchAmberTimeTicking(bool ticking);

private:
    Ui::ShadowsView *ui;
    QTimer *m_amberTimer;
    QAmberSurroundingsTableModel *m_amberModel;
    QString m_amberLog;

    mutable std::mutex m_amberChangeGuard;
    amber::Amber m_amber;

    void evalAmberTask(const amber::AmberTask& task);
    void changeAmber(const amber::AmberTask& task);

    void updateUI(const amber::Amber &amber);
    void appendAmberLog(const amber::Log& log);
};

#endif // SHADOWSVIEW_H

