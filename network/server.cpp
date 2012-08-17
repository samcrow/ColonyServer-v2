#include "server.hpp"

//Define constants
const int Server::port = 7510;

Server::Server(ClientModel *model, ColonyModel *colonyModel, QObject *parent) :
    QTcpServer(parent)
{
    Q_ASSERT(model != 0);
    this->model = model;
    this->colonyModel = colonyModel;
}


void Server::start() {
    bool ret = listen(QHostAddress::Any, port);

    if(!ret) {
        qCritical() << "Failed to bind to listen for connections on port" << port;
    } else {
        qDebug() << "Successfully bound to port" << port;
    }
}

void Server::incomingConnection(int handle) {
    qDebug() << "New connection! Handle" << handle;

    Client * newClient = new Client(this);
    bool ret = newClient->setSocketDescriptor(handle);

    if(!ret) {
        qWarning() << "Could not open a client connection to a socket with handle" << handle;
    }

    //Hook up signals
    connect(newClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    //Hook up the socket to a protocol object
    //Create it as a child of the socket so they'll get deleted at the same time
    Protocol *protocol = new JSONProtocol(newClient);
    protocol->setIODevice(newClient);
    protocol->setModel(colonyModel);

    model->appendClient(newClient); // Add the new client to the data model

    emit newConnection();
}

//Slot invoked when an error occurs
void Server::socketError(QAbstractSocket::SocketError /*error*/) {
    //Get the client that sent the error
    Client * sender = qobject_cast<Client *>(QObject::sender());
    Q_ASSERT(sender != 0);//Assert that the cast was successful

    qDebug() << "Error with" << sender->localAddress().toString() << ":" << sender->errorString();
    model->removeClient(sender);

    //The socket has been dealt with and is done.
    //Remove it from memory.
    //delete sender;
}

