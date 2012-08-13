#ifndef PROTOCOLINTERFACE_HPP
#define PROTOCOLINTERFACE_HPP

#include <QString>

#include "data/colonymodel.hpp"

/**
  A base class for implementations of the protocol to send & receive colony data
  */
/*abstract*/ class ProtocolInterface
{
public:
    ProtocolInterface();

    /**
      Parse a string of text. Do what it wants with the data model.
      The details of this are implementation-specific.
      */
    virtual void parseInput(QString input, ColonyModel &model) = 0;

};

#endif // PROTOCOLINTERFACE_HPP
