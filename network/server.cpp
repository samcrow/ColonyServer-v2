#include "server.hpp"

//Define constants
const int Server::port = 7510;

Server::Server(ClientModel *model, QObject *parent) :
    QTcpServer(parent)
{
    Q_ASSERT(model != 0);
    this->model = model;
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

