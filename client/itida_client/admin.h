#ifndef ADMIN_MANAGER_H
#define ADMIN_MANAGER_H

#include "client.h" // Including base class header

class AdminManager : public Client
{
    Q_OBJECT // Required for signals and slots


public:
    // Constructor
    explicit AdminManager();

    // Functions to perform admin operations
    void viewAccount();
    void getAccountNumber();
    void viewBankDatabase();
    void createNewUser();
    void deleteUser();
    void updateUser();
    void viewTransactionHistory();
    void sendRequestToServer();
    bool login();
    void start(bool&);

signals:
public slots:
    // Slot functions for network communication
    void connectToHost(QString host, quint16 port);
    void disconnect();

protected slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readyRead();

private:
    QTcpSocket socket; // Socket for communication
    QDataStream outStream; // Data stream for outgoing data
    QDataStream inStream; // Data stream for incoming data
    QString adminName; // Admin name
};

#endif // ADMIN_MANAGER_H
