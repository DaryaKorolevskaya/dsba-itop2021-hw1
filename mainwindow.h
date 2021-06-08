#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QCalendarWidget>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>
#include <QDate>
#include <QTextStream>
#include <QComboBox>
#include <QPushButton>
#include <QtCharts>
#include <QPixmap>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_infected_clicked();

    void on_died_clicked();

    void on_calendarWidget_1_clicked(const QDate &date);

    void on_calendarWidget_2_clicked(const QDate &date);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_actionLoad_data_from_csv_triggered();

    void on_actionAbout_Application_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QCalendarWidget *calendar;
    QLabel *label;
    QCheckBox *box;
    QDate *date;
    QComboBox *combobox;
    QPushButton *button;
    QGraphicsView *graphic;
    QMenuBar *menubar;


};
#endif // MAINWINDOW_H
