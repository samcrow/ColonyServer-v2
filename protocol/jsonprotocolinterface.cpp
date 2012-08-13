#include "jsonprotocolinterface.hpp"

JSONProtocolInterface::JSONProtocolInterface()
{
}

void JSONProtocolInterface::parseInput(QString input, ColonyModel &model) {
    //Parse the string into JSON
    QJson::Parser parser;
    bool ok;
    QVariantMap jsonRoot = parser.parse(input.toUtf8(), &ok).toMap();

    if(!ok) {
        qWarning() << "Failed to parse JSON!";
        return;
    }

    QString request = jsonRoot.value("request").toString();

    if(request == "get colonies") {

    }
}
