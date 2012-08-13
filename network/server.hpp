#ifndef SERVER_HPP
#define SERVER_HPP

#include <QObject>
#include <QDebug>
#include <QtGlobal>
#include <QMetaEnum>
#include <QtNetwork/QTcpServer>

#include "client.hpp"
#include "data/clientmodel.hpp"

/**
  Manages the TCP server.
  This implementation directly adds new connections to the parent's data model.
  It emits the signal newConnection() but does not deal with pending connections.
  */
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(ClientModel * model, QObject * parent = 0);

protected:
    //Override from QTcpServer
    void incomingConnection(int handle);

private:

    /** The local port number that clients should connect to */
    static const int port;

    /**
      The data model
      */
    ClientModel *model;


signals:

public slots:
    /**
      Start the server and begin accepting connections
      */
    void start();


private slots:

    void socketError(QAbstractSocket::SocketError error);
};

#endif // SERVER_HPP
