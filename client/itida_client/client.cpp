#include "client.h"
#include <QTextStream>
#include <QDataStream>
#include <QDebug>

//It provides functionality for running external processes.
//QProcess to start, manage, and communicate with external programs from within their Qt applications.
#include<QProcess>
//It provides information about the system on which the application is running.
// QSysInfo to query various system properties such as the operating system version, architecture, and more...
//... This information can be useful for making runtime decisions or logging system-specific details.
#include<QSysInfo>

Client::Client(QObject *parent)
    : QObject(parent)
{
    // Initialize the request flag to "General"
    requestFlag = "General";
}

// Function to clear the console screen
void Client::clearScreen()
{
    // Use system command to clear the console screen
    system("cls");
}

