#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <vector>
#include "covidData.h"

class myTableModel : public QAbstractTableModel
{


public:

    QString sel_country;

    void loadFrom(std::vector<covidData>& myData);

    int rowCount(const QModelIndex&) const override;

    int columnCount(const QModelIndex&) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;



private:
        std::vector<covidData> covData;
};






#endif // MODEL_H
