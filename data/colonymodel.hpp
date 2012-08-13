#ifndef COLONYMODEL_HPP
#define COLONYMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QDebug>
#include <QVariant>

#include <colony.hpp>

class ColonyModel : public QAbstractTableModel, QList<Colony *>
{
    Q_OBJECT
public:
    explicit ColonyModel(QObject *parent = 0);

    //Implementations of abstract model methods
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /** Add a colony to the model */
    void appendColony(Colony *const&t);
    /** Remove a colony from the model */
    void removeColony(Colony *const&t);

signals:

public slots:

private slots:

    //Connectd to the dataChanged() signal of each colony.
    void colonyDataChanged();

};

#endif // COLONYMODEL_HPP
