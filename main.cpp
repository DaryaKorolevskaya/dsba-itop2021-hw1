#include "mainwindow.h"

#include <QApplication>
#include "covidData.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<covidData> covid;
    fillMap(covid);
    return a.exec();
}
