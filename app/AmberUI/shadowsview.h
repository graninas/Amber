#ifndef SHADOWSVIEW_H
#define SHADOWSVIEW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QTimer>
#include <mutex>

#include <amber.h>

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
    QString m_amberLog;

    mutable std::mutex m_amberChangeGuard;
    amber::Amber m_amber;

    void evalAmberTask(const amber::AmberTask& task);
    void evaluateTasks(const std::list<amber::AmberTask>& tasks);

    void changeAmber(const amber::AmberTask& task);

    void updateUI(const amber::Amber &amber);
    void appendAmberLog(const amber::Log& log);
};

#endif // SHADOWSVIEW_H
