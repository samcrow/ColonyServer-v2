#ifndef JSONPROTOCOLINTERFACE_HPP
#define JSONPROTOCOLINTERFACE_HPP

#include <qjson/parser.h>

#include "protocolinterface.hpp"

/**
  Here's the complete specification of the JSON protocol:

  To request the list of colonies, the client sends {"request": "get colonies"}
  The server responds {"status": "success", "colonies": [ {colony1} (...) ] }

  To update one colony, the client sends {"request": "update colony", "colony": {"id" (...) } }
  The server responds {"status": "success"}
  If an error occurred, the server may respond {"status": "failure", "message" : (An error message) } to give an error message.
  */

class JSONProtocolInterface : public ProtocolInterface
{
public:
    JSONProtocolInterface();

    void parseInput(QString input, ColonyModel &model);



    /** Using the given model, create a QVariantList of all the colonies it contains */
    QVariantList makeColonyList(ColonyModel &model);
};

#endif // JSONPROTOCOLINTERFACE_HPP
