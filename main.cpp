#include "mainwindow.h"
#include <iostream>
#include <QApplication>






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow w;
    w.show();



    //QCalendarWidget *calendar = new QCalendarWidget;
    //calendar->setGridVisible(true);
    //calendar->setDateRange(QDate(2020, 1, 1), QDate(2021, 1, 1));
    //calendar->show();
    return a.exec();
}
