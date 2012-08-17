#include "colonyserver.hpp"
#include "ui_colonyserver.h"

ColonyServer::ColonyServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ColonyServer)
{
    ui->setupUi(this);

    clientModel = new ClientModel(this);
    colonyModel = new ColonyModel(this);
    server = new Server(clientModel, colonyModel, this);

    ui->clientTable->setModel(clientModel);
    //Resize each column to fit
    for(int i = 0, max = clientModel->columnCount(QModelIndex()); i < max; i++) {
        ui->clientTable->resizeColumnToContents(i);
    }

    ui->colonyTable->setModel(colonyModel);
    //Resize each column to fit
    //Each 50px (or 50 some other units) wide
    ui->colonyTable->setColumnWidth(0, 50);
    ui->colonyTable->setColumnWidth(1, 50);
    ui->colonyTable->setColumnWidth(2, 50);
    ui->colonyTable->setColumnWidth(3, 50);
    ui->colonyTable->setColumnWidth(4, 50);

    //Test colony
    Colony *c1 = new Colony(2791, 8562, 3237, true);
    c1->setVisited(true);
    colonyModel->appendColony(c1);

    //Set up actions

    //Add actions to the toolbar
    ui->toolBar->insertAction(NULL, ui->configureInterfaceAction);
    ui->toolBar->insertAction(NULL, ui->openCsvAction);

    server->start();

}

void ColonyServer::configureNetwork() {
    NetworkConfigurator conf;
    conf.configure();
}

ColonyServer::~ColonyServer()
{
    delete ui;
}
