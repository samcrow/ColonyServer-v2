#ifndef JSONPROTOCOL_HPP
#define JSONPROTOCOL_HPP

#include <qjson/parser.h>
#include <qjson/serializer.h>
#include <colony.hpp>

#include "protocol.hpp"


/**
  Implements a protocol using JSON as a file transfer format

  Here's the complete specification of the JSON protocol:

  To request the list of colonies, the client sends {"request": "get colonies"}
  The server responds {"status": "success", "colonies": [ {colony1} (...) ] }

  To update one colony, the client sends {"request": "update colony", "colony": {"id" (...) } }
  The server responds {"status": "success"}
  If an error occurred, the server may respond {"status": "failure", "message" : (An error message) } to give an error message.

  The update colony request syntax may also be used to insert a new colony into the data set.
  To do that, simply specify a colony ID that's not currently in the data set.
  For safety, you should specify all the data about the colony (including ID, x, y, active, and visited).
  */
class JSONProtocol : public Protocol
{
    Q_OBJECT
public:
    explicit JSONProtocol(QObject *parent);

protected:

    /**
      This is called from the superclass
      */
    void respondTo(QByteArray request);

private:

    /**
      This is called from respondTo(QByteArray). This decides which special action function to call
      */
    void respondToRequest(QVariantMap request);

    /**
      Output the list of colonies to the IO device
      */
    void printColonies();

    /**
      Output a message indicating failure and a given error message.
      The message will be sent to the client
      and printed to the console using qWarning().
      */
    void printError(QString message);

    /**
      Print a success message to the IO device
      */
    void printSuccess();

    /**
      Print a generic set of JSON data to the IO device
      */
    void printJSON(QVariantMap json);

    /**
      Takes a JSON map of data for one colony
      If a colony with the given ID exists in the data model, update it with the new data
      If no colony with the given ID exists, create a new colony with the given data and add it to the model
      */
    void updateColony(QVariantMap colonyJson);

signals:

public slots:

};

#endif // JSONPROTOCOL_HPP
