#ifndef SERVER_HPP
#define SERVER_HPP

#include <QObject>
#include <QDebug>
#include <QtGlobal>
#include <QMetaEnum>
#include <QtNetwork/QTcpServer>

#include "client.hpp"
#include "protocol/protocol.hpp"
#include "protocol/jsonprotocol.hpp"
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
    explicit Server(ClientModel * model, ColonyModel * colonyModel, QObject * parent);

protected:
    //Override from QTcpServer
    void incomingConnection(int handle);

private:

    /** The local port number that clients should connect to */
    static const int port;

    /**
      The client data model
      */
    ClientModel *model;

    /**
      The colony data model
      */
    ColonyModel *colonyModel;

    /**
      The protocol that handles the response
      */
    Protocol *protocol;

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
