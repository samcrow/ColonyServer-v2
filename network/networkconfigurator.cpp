#include "networkconfigurator.hpp"

//Define constants
const QString NetworkConfigurator::networkName = "Colony Navigator";
const QString NetworkConfigurator::networkPassword = "254colonies";

const QHostAddress NetworkConfigurator::localAddress = NetworkConfigurator::getLocalAddress();
const QHostAddress NetworkConfigurator::subnetMask = NetworkConfigurator::getSubnetMask();
const QHostAddress NetworkConfigurator::defaultGateway = NetworkConfigurator::getDefaultGateway();

NetworkConfigurator::NetworkConfigurator()
{

}

#ifdef Q_OS_MAC
void NetworkConfigurator::configureMac() {
    //Interface name, for example "en1"
    const QString interfaceName = "AirPort";//Hard-coded.
    qDebug() << "Configuring" << interfaceName << "...";

    //Ensure that airport is on
    const QString airportOnCommand = "networksetup -setairportpower "+interfaceName+" on";

    QProcess airportOnProcess;
    qDebug() << "About to turn airport on: execute" << airportOnCommand;
    int onRet = airportOnProcess.execute(airportOnCommand);
    if(onRet != 0) {
        qDebug() <<
           "The command returned" << onRet << ". This may indicate a failiure. Check stdout for more information.";
    } else {
        qDebug() << "Airport on.";
    }

    //Connect to the network
    const QString connectCommand
            = "networksetup -setairportnetwork "+interfaceName+" \""+networkName+"\" \""+networkPassword+"\"";
    qDebug() << "About to connect to network: Execute" << connectCommand;
    QProcess connectProcess;
    int connectRet = connectProcess.execute(connectCommand);
    if(connectRet != 0) {
        qDebug() <<
           "The command returned" << connectRet << ". This may indicate a failiure. Check stdout for more information.";
    } else {
        qDebug() << "Connecting done.";
    }

    //Set up the IP address and such
    const QString ipConfigCommand = "networksetup -setmanual "
            +interfaceName+" "+localAddress.toString()+" "+subnetMask.toString()+" "+defaultGateway.toString();
    qDebug() << "About to configure IP addresses: Execute" << ipConfigCommand;
    QProcess configProcess;
    int configRet = configProcess.execute(ipConfigCommand);
    if(configRet != 0) {
        qDebug() <<
           "The command returned" << configRet << ". This may indicate a failiure. Check stdout for more information.";
    } else {
        qDebug() << "IP configuration done.";
    }
}
#endif

void NetworkConfigurator::configure() {

#ifdef Q_OS_MAC
    configureMac();
#endif

#ifdef Q_OS_UNIX
#ifndef Q_OS_MAC
    configureUnix();
#endif
#endif

#ifdef Q_OS_WIN
    configureWindows();
#endif

#ifndef Q_OS_WIN
#ifndef Q_OS_UNIX
#warning "Neither Q_OS_WIN nor Q_OS_UNIX was defined! The network configurator will not work!"
#endif
#endif
}

#ifdef Q_OS_UNIX
#ifndef Q_OS_MAC
void NetworkConfigurator::configureUnix() {
    qWarning() << "Warning: Unix network configuration is not done. You will have to configure the network manually.";
}
#endif
#endif

#ifdef Q_OS_WIN
void NetworkConfigurator::configureWindows() {
    qWarning() << "Warning: Windows network configuration is not done. You will have to configure the network manually.";;
}
#endif

QHostAddress NetworkConfigurator::getLocalAddress() {
    QHostAddress address;
    address.setAddress("10.0.0.2");
    return address;
}
QHostAddress NetworkConfigurator::getSubnetMask() {
    QHostAddress address;
    address.setAddress("255.255.255.0");
    return address;
}
QHostAddress NetworkConfigurator::getDefaultGateway() {
    QHostAddress address;
    address.setAddress("10.0.0.1");
    return address;
}
