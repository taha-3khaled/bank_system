#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

//header is part of the Qt framework and provides functionality related to meta-object information,...
//...including enums. It allows you to introspect enums at runtime,
//which can be useful for tasks like translating enum values to human-readable strings.
#include <QMetaEnum>

 #include <windows.h>
//is a header file for Windows-specific functions and data types.
//It provides access to various Windows API functions and definitions,
//allowing you to interact with the Windows operating system directly.
//In this case, it's used for the system("cls") call in the clearScreen() function to clear the console screen,
//which is a Windows-specific command.


class Client : public QObject
{
    Q_OBJECT
public:
    // Constructor with optional parent parameter
    explicit Client(QObject *parent = nullptr);

    // Pure virtual functions for handling account number, account viewing,....
   //.... transaction history, sending requests, and login
    virtual void getAccountNumber() = 0;
    virtual void viewAccount() = 0;
    virtual void viewTransactionHistory() = 0;
    virtual void sendRequestToServer() = 0;
    virtual bool login() = 0;
    void clearScreen();

protected:
    // Member variables
    QString role;
    QString request;
    QVariant serverResponse;
    QString requestFlag;
};

#endif // CLIENT_H_INCLUDED
