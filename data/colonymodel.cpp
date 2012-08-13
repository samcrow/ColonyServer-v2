#include "colonymodel.hpp"

ColonyModel::ColonyModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

void ColonyModel::appendColony(Colony *const&t) {
    int newIndex = length();
    beginInsertRows(QModelIndex(), newIndex, newIndex);
    QList<Colony *>::append(t);
    endInsertRows();

    //Hook up the mechanism to be notified when anything about this colony changes
    connect(t, SIGNAL(dataChanged()), this, SLOT(colonyDataChanged()));
}

void ColonyModel::removeColony(Colony *const&t) {
    int index = indexOf(t);

    if(index == -1) {
        qWarning() << "This item is not in the colony data model. It could not be removed.";
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    QList<Colony *>::removeOne(t);
    endRemoveRows();

    //Disconnect the mechanism - this colony's done with.
    disconnect(t, SIGNAL(dataChanged()), this, SLOT(colonyDataChanged()));
}

//Each colony in the model calls this when it is changed
void ColonyModel::colonyDataChanged() {
    //Get the colony that was changed
    Colony *changedColony = qobject_cast<Colony *>(sender());
    Q_ASSERT(changedColony != 0);

    int index = indexOf(changedColony);
    if(index == -1) {
        qWarning() << "Got a dataChanged() signal from a colony not in the list!";
        return;
    }
    //Tell the view that it was changed
    QModelIndex left = createIndex(index, 0);
    QModelIndex right = createIndex(index, 4);
    emit dataChanged(left, right);
}

QVariant ColonyModel::data(const QModelIndex &index, int role) const {

    if(role == Qt::DisplayRole) {

        switch(index.column()) {
        case 0:
            //Left column: ID
            return at(index.row())->getID(); // Return the ID of this item
            break;
        case 1:
            return at(index.row())->getX();
            break;
        case 2:
            //Column 2: Y
            return at(index.row())->getY();
            break;
        case 3:
            //Column 3: visited
            return at(index.row())->isVisited() ? "Yes" : "No";
        case 4:
            //Column 4: active
            return at(index.row())->isVisited() ? "Yes" : "No";
        default:
            return QVariant();
            break;
        }

    } else {
        //Return an invalid QVariant for roles other than display
        return QVariant();
    }
}

QVariant ColonyModel::headerData(int section, Qt::Orientation orientation, int role) const {

    //Customize the display
    if(role == Qt::DisplayRole) {

        if(orientation == Qt::Horizontal) {
            switch(section) {
            case 0:
                return "ID";
                break;
            case 1:
                return "X";
                break;
            case 2:
                return "Y";
                break;
            case 3:
                return "Visited";
                break;
            case 4:
                return "Active";
                break;
            default:
                return QVariant();
                break;
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

int ColonyModel::rowCount(const QModelIndex &/*parent*/) const {
    return length();
}

int ColonyModel::columnCount(const QModelIndex &/*parent*/) const {
    //Always 5 columns
    return 5;
}
