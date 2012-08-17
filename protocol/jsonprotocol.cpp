#include "jsonprotocol.hpp"

JSONProtocol::JSONProtocol(QObject *parent) :
    Protocol(parent)
{

}

void JSONProtocol::respondTo(QByteArray request) {

    bool ok;
    QJson::Parser parser;
    QVariant json = parser.parse(request, &ok);

    if(!ok) {
        printError("Request was not valid JSON");
        return;
    }

    QVariantMap jsonMap = json.toMap();
    respondToRequest(jsonMap);
}

void JSONProtocol::respondToRequest(QVariantMap request) {
    QString requestString = request.value("request").toString();
    if(requestString.isEmpty()) {
        printError("No request specified.");
        return;
    }


    if(requestString == "get colonies") {
        printColonies();
        return;
    }
    else if(requestString == "update colony") {
        QVariantMap colonyJson = request.value("colony").toMap();
        updateColony(colonyJson);
    }
    else {
        printError("Unrecognized request \""+requestString+"\"");
    }
}

void JSONProtocol::printColonies() {

    QVariantMap json;

    QVariantList colonyList;

    for(int i = 0, max = model->length(); i < max; i++) {
        Colony *colony = model->at(i);
        QVariant colonyJson = colony->toVariant();
        colonyList.append(colonyJson);
    }

    json.insert("colonies", colonyList);

    json.insert("status", "success");

    printJSON(json);
}

void JSONProtocol::updateColony(QVariantMap colonyJson) {
    int id = colonyJson.value("id").toInt();

    Colony *colonyWithId = model->getColonyById(id);

    if(colonyWithId != NULL) {
        //Colony with this ID exists; update it
        //Change only the values that were given

        colonyWithId->setX(colonyJson.value("x", colonyWithId->getX()).toDouble());
        colonyWithId->setY(colonyJson.value("y", colonyWithId->getY()).toDouble());
        colonyWithId->setVisited(colonyJson.value("visited", colonyWithId->isVisited()).toBool());
        colonyWithId->setActive(colonyJson.value("active", colonyWithId->isActive()).toBool());
    }
    else {
        //Add a new colony
        Colony *colony = new Colony(colonyJson.value("id", 0).toInt(), 0, 0, false);

        //Ensure that everything's set to zero
        colony->setX(0);
        colony->setY(0);
        colony->setVisited(false);
        colony->setActive(false);

        colony->setX(colonyJson.value("x", colony->getX()).toDouble());
        colony->setY(colonyJson.value("y", colony->getY()).toDouble());
        colony->setVisited(colonyJson.value("visited", colony->isVisited()).toBool());
        colony->setActive(colonyJson.value("active", colony->isActive()).toBool());

        model->appendColony(colony);
    }
}

void JSONProtocol::printSuccess() {
    QVariantMap json;
    json.insert("status", "success");
    printJSON(json);
}

void JSONProtocol::printError(QString message) {
    qWarning() << "JSON protocol error:" << message;

    QVariantMap json;
    json.insert("status", "failure");
    json.insert("message", message);

    printJSON(json);
}

void JSONProtocol::printJSON(QVariantMap json) {
    QJson::Serializer serializer;
    serializer.setIndentMode(QJson::IndentCompact);

    QByteArray jsonText = serializer.serialize(json);

    io->write(jsonText);
    io->write("\n");//Print a newline to finish it

}
