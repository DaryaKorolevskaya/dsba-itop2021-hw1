#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "model.h"






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/img/img/covdata.png");
    int w = ui->image->width();
    int h = ui->image->height();
    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));


    calendar = new QCalendarWidget;
    box = new QCheckBox;
    ui->calendarWidget_1->setDateRange(QDate(2019, 12, 31), QDate(2020, 11, 5));
    ui->calendarWidget_2->setDateRange(QDate(2019, 12, 31), QDate(2020, 11, 5));



}

MainWindow::~MainWindow()
{
    delete ui;
    delete myModel;
}




void MainWindow::on_infected_clicked()
{
    if(ui->infected->isChecked())
    {
        info.infected = 1;
    }
}


void MainWindow::on_died_clicked()
{
    if(ui->died->isChecked())
    {
        info.died = 1;
    }
}

void MainWindow::on_calendarWidget_1_clicked(const QDate &date)
{
    QDate d1;
    d1 = date;
    QString qstr = d1.toString();
    info.date_from = qstr.toStdString();


}

void MainWindow::on_calendarWidget_2_clicked(const QDate &date)
{
    QDate d2;
    d2 = date;
    QString qstr2 = d2.toString();
    info.date_to = qstr2.toStdString();

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

    QString cntr = arg1;
    myModel->sel_country = arg1;
    info.selected_country = cntr.toStdString();






}

void MainWindow::on_pushButton_clicked()
{
    info.result = covidData::computing(info.covid, info.date_from, info.date_to, info.selected_country, info.infected, info.died);
    if (ui->died->isChecked() && ui->infected->isChecked()){

        QBarSet *set0 = new QBarSet("Died");
        QBarSet *set1 = new QBarSet("Infected");
        int max_i = 0;

        for(auto it = info.result.second.begin(); it != info.result.second.end(); ++it)
          {
            *set0 << it->second;
          }

        for(auto it = info.result.first.begin(); it != info.result.first.end(); ++it)
          {
            if (it->second > max_i)
                max_i = it->second;
            *set1 << it->second;
          }

         QBarSeries *series = new QBarSeries();
         series->append(set0);
         series->append(set1);

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setAnimationOptions(QChart::SeriesAnimations);

         QStringList categories;
         for(auto it = info.result.first.begin(); it != info.result.first.end(); ++it)
           {
               categories << QString::fromStdString(it->first);
           }
         QBarCategoryAxis *axisX = new QBarCategoryAxis();
         axisX->append(categories);
         chart->addAxis(axisX, Qt::AlignBottom);
         series->attachAxis(axisX);

         QValueAxis *axisY = new QValueAxis();
         axisY->setRange(0,max_i);
         chart->addAxis(axisY, Qt::AlignLeft);
         series->attachAxis(axisY);


         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignBottom);

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);


         ui->graphicsView->setViewport(chartView);

    }
    else {
        if (ui->died->isChecked()){

            QBarSet *set0 = new QBarSet("Died");
            int max_d = 0;

            for(auto it = info.result.second.begin(); it != info.result.second.end(); ++it)
              {
                if (it->second > max_d)
                    max_d = it->second;
                *set0 << it->second;
              }


             QBarSeries *series = new QBarSeries();
             series->append(set0);

             QChart *chart = new QChart();
             chart->addSeries(series);
             chart->setAnimationOptions(QChart::SeriesAnimations);

             QStringList categories;
             for(auto it = info.result.first.begin(); it != info.result.first.end(); ++it)
               {
                   categories << QString::fromStdString(it->first);
               }
             QBarCategoryAxis *axisX = new QBarCategoryAxis();
             axisX->append(categories);
             chart->addAxis(axisX, Qt::AlignBottom);
             series->attachAxis(axisX);

             QValueAxis *axisY = new QValueAxis();
             axisY->setRange(0,max_d);
             chart->addAxis(axisY, Qt::AlignLeft);
             series->attachAxis(axisY);


             chart->legend()->setVisible(true);
             chart->legend()->setAlignment(Qt::AlignBottom);

             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);

             ui->graphicsView->setViewport(chartView);

        }

        if (ui->infected->isChecked()){

            QBarSet *set1 = new QBarSet("Infected");
            int max_i = 0;

            for(auto it = info.result.first.begin(); it != info.result.first.end(); ++it)
              {
                if (it->second > max_i)
                    max_i = it->second;
                *set1 << it->second;
              }



             QBarSeries *series = new QBarSeries();
             series->append(set1);

             QChart *chart = new QChart();
             chart->addSeries(series);
             chart->setAnimationOptions(QChart::SeriesAnimations);

             QStringList categories;
             for(auto it = info.result.first.begin(); it != info.result.first.end(); ++it)
               {
                   categories << QString::fromStdString(it->first);
               }
             QBarCategoryAxis *axisX = new QBarCategoryAxis();
             axisX->append(categories);
             chart->addAxis(axisX, Qt::AlignBottom);
             series->attachAxis(axisX);

             QValueAxis *axisY = new QValueAxis();
             axisY->setRange(0,max_i);
             chart->addAxis(axisY, Qt::AlignLeft);
             series->attachAxis(axisY);


             chart->legend()->setVisible(true);
             chart->legend()->setAlignment(Qt::AlignBottom);

             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);

             ui->graphicsView->setViewport(chartView);
        }
    }


}


void MainWindow::on_actionLoad_data_from_csv_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "C://",
                                                    "CSV file (*.csv)");
    ui->statusbar->showMessage(filename + " is loaded.");

    std::string fname = filename.toStdString();
    covidData::fillMap(info.covid, info.countries, fname);
    std::vector<covidData> covData = info.covid;
    std::set<std::string>::iterator it;

    for(auto &item : info.countries){
        QString str = QString::fromStdString(item);
        ui->comboBox->addItem(str);
    }
    myModel->loadFrom(info.covid);
    ui->tableView->setModel(myModel);


}

void MainWindow::on_actionAbout_Application_triggered()
{
    QMessageBox::about(this, "About Application", "You can choose beginning and end date on calendars and country."
" After that choose 'infected' or/and 'died' to see bar charts with statistic.");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

