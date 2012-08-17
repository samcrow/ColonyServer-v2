#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <QObject>
#include <QIODevice>
#include <QByteArray>

#include "../data/colonymodel.hpp"

/**
  An abstract base class for an implementation of a protocol.
  A protocol connects to a QIODevice and uses the signal/slot mechanism
  to respond to data received from the device
  and send data back to the device.
  */
class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent);

    /**
      Set the I/O device that this protocol instance should read to and write from
      */
    void setIODevice(QIODevice * const device);

    /**
      Set the data model that this protocol instance should interact with
      */
    void setModel(ColonyModel * model);

protected:

    /** The device to use to read/write data */
    QIODevice *io;

    /** The data model containing the colonies */
    ColonyModel *model;

    /**
      This is called when a new line of data (delimited by \n)
      is recieved. That line of data is passed into this function.
      Implementations may access the IO device io to send a response.
      */
    virtual void respondTo(QByteArray request) = 0;

protected slots:
    /*
       Connected to QIODevice::readyRead(). Called when new data is received.
      */
    void readyRead();

};

#endif // PROTOCOL_HPP
