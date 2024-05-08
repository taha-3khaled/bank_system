#include <QCoreApplication>
#include <QDebug>
#include "user.h"
#include "admin.h"
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    QString role;
    bool isLogged = false;

    qInfo() << "Welcome to the bank system\nPlease choose\"user\" or \"admin\" or \"exit\"";
    std::string clientRole;
    std::cin >> clientRole;
    std::cout << "User input: " << clientRole << std::endl;
    role = QString::fromStdString(clientRole);

    if (role.toUpper() == "USER")
    {
        UserManager user;
        user.connectToHost("192.168.1.9", 123454);

        while (!isLogged)
        {
            isLogged = user.login();
            user.clearScreen();

            if (!isLogged)
                qInfo("Username or Password is wrong!!\nPlease Try Again");
        }

        while (isLogged)
        {
            user.start(isLogged);
        }
    }
    else if (role.toUpper() == "ADMIN")
    {
        AdminManager admin;
        admin.connectToHost("192.168.1.9", 123454);

        while (!isLogged)
        {
            isLogged = admin.login();
            admin.clearScreen();

            if (!isLogged)
                qInfo("Username or Password is wrong!!\nPlease Try Again");
        }

        while (isLogged)
        {
            admin.start(isLogged);
        }
    }
    else if (role.toUpper() == "EXIT")
    {
        qInfo() << "Thank you!....System is closing..";
        QCoreApplication::exit(0);
    }
    else
    {
        qInfo() << "Sorry, you're entering an invalid input";
    }

    qInfo() << "Thank you for using or banking system ...see you soon ";
    QCoreApplication::exit(0);
    return a.exec();
}
