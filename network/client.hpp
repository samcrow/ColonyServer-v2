#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>

/**
  A connection to a client device.
  This adds additional support for getting & sending data.
  */
class Client : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    /** Get this client's arbitrary ID. This value should only be used in the user interface. */
    int getId();

signals:

public slots:


private:
    /** The number of clients that have been allocated. Increment this when constructing one. */
    static int allocationCount;

    /** A pretty arbitrary ID for this client. This is used only in the user interface. */
    int id;
};


#endif // CLIENT_HPP
