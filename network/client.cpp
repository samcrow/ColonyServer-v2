#include "client.hpp"

//Init static members
int Client::allocationCount = 0;

Client::Client(QObject *parent) :
    QTcpSocket(parent)
{
    //Increment the allocation count and assign it as this one's ID
    allocationCount++;
    id = allocationCount;
}

int Client::getId() {
    return id;
}
