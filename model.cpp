#include "model.h"
#include "mainwindow.h"

void myTableModel::loadFrom(std::vector<covidData>& myData)
{
    covData = myData;

}

int myTableModel::columnCount(const QModelIndex&) const
{
    return 10;
}

int myTableModel::rowCount(const QModelIndex&) const
{
    return covData.size();
}

QVariant myTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundColorRole) {
        if (index.model()->data(
                    index.model()->index(index.row(), 5),
                    Qt::DisplayRole) == sel_country){
            return QVariant(QColor("#689581"));
        }
    }

    if (role == Qt::DisplayRole)
    {
        int i = index.column();
        switch (i)
        {
            case(0): return QVariant(QString::number(covData[index.row()].day));
            case(1): return QVariant(QString::number(covData[index.row()].month));
            case(2): return QVariant(QString::number(covData[index.row()].year));
            case(3): return QVariant(QString::number(covData[index.row()].cases));
            case(4): return QVariant(QString::number(covData[index.row()].deaths));
            case(5): return QVariant(QString::fromStdString(covData[index.row()].country));
            case(6): return QVariant(QString::fromStdString(covData[index.row()].code));
            case(7): return QVariant(QString::number(covData[index.row()].population));
            case(8): return QVariant(QString::fromStdString(covData[index.row()].continent));
            case(9): return QVariant(QString::number(covData[index.row()].rate));
        }
    }



    return QVariant();
}

QVariant myTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        int i = section;
        switch (i)
        {
            case(0): return QVariant(QString("Day"));
            case(1): return QVariant(QString("Month"));
            case(2): return QVariant(QString("Year"));
            case(3): return QVariant(QString("Cases"));
            case(4): return QVariant(QString("Deaths"));
            case(5): return QVariant(QString("Country"));
            case(6): return QVariant(QString("Code"));
            case(7): return QVariant(QString("Population"));
            case(8): return QVariant(QString("Continent"));
            case(9): return QVariant(QString("Rate"));
        }
    }
    return QVariant();
}



