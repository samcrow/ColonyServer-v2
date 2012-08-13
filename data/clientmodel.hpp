#ifndef CLIENTMODEL_HPP
#define CLIENTMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QLabel>
#include <QtNetwork/QHostAddress>

#include "../network/client.hpp"

/**
  Stores a set of clients and interfaces with the client table in the UI
  */
class ClientModel : public QAbstractTableModel, QList<Client *> //Multiple inheritance yay!
{
    Q_OBJECT
public:
    explicit ClientModel(QObject *parent = 0);

    //Implementations of abstract model methods
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /** Add a client to the model */
    void appendClient(Client *const&t);
    /** Remove a client from the model */
    void removeClient(Client *const&t);


signals:

public slots:

private:

};

#endif // CLIENTMODEL_HPP
