#ifndef NETWORKCONFIGURATOR_HPP
#define NETWORKCONFIGURATOR_HPP

#include <QtGlobal>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QHostAddress>

class NetworkConfigurator
{
public:
    NetworkConfigurator();

    /**
      Connect to the network and set the IP address. This may or may not block.
      */
    void configure();

private:

    //Constants

    /** Name of the Wi-Fi network to connect to */
    static const QString networkName;
    /** Password to use connecting to the network */
    static const QString networkPassword;
    /** IP address to set the local wirless interface to */
    static const QHostAddress localAddress;
    /** Subnet mask to set the local wireless interface to */
    static const QHostAddress subnetMask;
    /** Default gateway to set the local wireless interface to */
    static const QHostAddress defaultGateway;

    //Static functions used to get configuration constants
    static QHostAddress getLocalAddress();
    static QHostAddress getSubnetMask();
    static QHostAddress getDefaultGateway();

    //Mac configure function: if mac
#ifdef Q_OS_MAC
    void configureMac();
#endif

    //Unix configure function: If unix and not mac
#ifdef Q_OS_UNIX
#ifndef Q_OS_MAC
    void configureUnix();
#endif
#endif
    //Windows configure function: If windows
#ifdef Q_OS_WIN
    void configureWindows();
#endif
};

#endif // NETWORKCONFIGURATOR_HPP
