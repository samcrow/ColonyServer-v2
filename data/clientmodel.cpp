#include "clientmodel.hpp"

ClientModel::ClientModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

QVariant ClientModel::data(const QModelIndex &index, int role) const {

    if(role == Qt::DisplayRole) {

        switch(index.column()) {
        case 0:
            //Left column
            return at(index.row())->getId(); // Return the ID of this item
            break;
        case 1:
            //right column
            return at(index.row())->peerAddress().toString();
            break;
        default:
            return QVariant();
            break;
        }

    } else {
        //Return an invalid QVariant for roles other than display
        return QVariant();
    }
}

QVariant ClientModel::headerData(int section, Qt::Orientation orientation, int role) const {

    //Customize the display
    if(role == Qt::DisplayRole) {

        if(orientation == Qt::Horizontal) {
            //Top header
            if(section == 0) {//Left column
                return "ID";
            }
            //Right column
            if(section == 1) {
                return "IP Address";
            }
        }

        //Other
        return QVariant();
    }
    else {
        //Just use the superclass implementation for roles other than display
        return QAbstractItemModel::headerData(section, orientation, role);
    }
}

int ClientModel::rowCount(const QModelIndex &/*parent*/) const {
    return length();
}

int ClientModel::columnCount(const QModelIndex &/*parent*/) const {
    //Always 2 columns
    return 2;
}

void ClientModel::appendClient(Client *const&t) {

    int newIndex = length();
    qDebug() << "Inserting row at index" << newIndex;

    //Get the view to update itself to reflect the new client
    beginInsertRows(QModelIndex(), newIndex, newIndex);
    QList<Client *>::append(t);//Add it to the list
    endInsertRows();
}

void ClientModel::removeClient(Client *const&t) {

    int indexToRemove = QList<Client *>::indexOf(t);
    qDebug() << "Removing row at index" << indexToRemove;

    beginRemoveRows(QModelIndex(), indexToRemove, indexToRemove);
    QList<Client *>::removeOne(t);
    endRemoveRows();
}
