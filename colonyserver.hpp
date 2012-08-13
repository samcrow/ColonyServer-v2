#ifndef COLONYSERVER_HPP
#define COLONYSERVER_HPP

#include <QtGlobal>
#include <QDebug>
#include <QAction>
#include <QMainWindow>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>

#include "network/networkconfigurator.hpp"
#include "network/server.hpp"
#include "data/clientmodel.hpp"
#include "data/colonymodel.hpp"

namespace Ui {
class ColonyServer;
}

class ColonyServer : public QMainWindow
{
    Q_OBJECT

private:
    Ui::ColonyServer *ui;


public:
    explicit ColonyServer(QWidget *parent = 0);
    ~ColonyServer();

    /**
      The data model containing the clients
      */
    ClientModel * clientModel;
    /**
      The data model containing the colonies
      */
    ColonyModel * colonyModel;

    /**
      The server
      */
    Server * server;

private slots:

    void configureNetwork();
};

#endif // COLONYSERVER_HPP
