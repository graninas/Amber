#include "amberview.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShadowsView w;
    w.show();

    return a.exec();
}
