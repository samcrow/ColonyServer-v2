#include "protocol.hpp"

Protocol::Protocol(QObject *parent) :
    QObject(parent)
{
    //Initialize pointers to NULL
    io = NULL;
    model = NULL;
}

void Protocol::readyRead() {

    //Assert that neither io nor model is NULL
    Q_ASSERT(io != NULL || io != 0);
    Q_ASSERT(model != NULL || io != 0);

    QByteArray line = io->readLine();


    respondTo(line);
}

void Protocol::setIODevice(QIODevice *const device) {
    //Undo the old connection if it exists
    if(io != NULL) {
        disconnect(io, SIGNAL(readyRead()), this, SLOT(readyRead()));
    }

    io = device;
    connect(io, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Protocol::setModel(ColonyModel *model) {
    this->model = model;
}
