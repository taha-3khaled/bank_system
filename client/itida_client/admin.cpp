#include "admin.h"
#include <iostream>
#include <QVariant>
#include <QVariantMap>
#include <conio.h>


AdminManager::AdminManager() : Client()
{
    // Setting up data stream for socket communication

    //This function call sets the device that the QDataStream will operate on....
    //...In this case, it sets the QTcpSocket socket as the device.
    //This means that any data written to outStream will be sent over the TCP socket represented by socket
    outStream.setDevice(&socket);

    //In Qt, QDataStream is a class used for serialization and deserialization of binary data to and from a QIODevice,
    //such as a file or a network socket. By setting the version of the data stream, you ensure that the data is serialized and deserialized correctly,
    //especially when dealing with data exchange between different versions of Qt applications or systems.
    outStream.setVersion(QDataStream::Qt_6_6);

    // when data is received on the TCP socket, it can be read from inStream
    inStream.setDevice(&socket);

    inStream.setVersion(QDataStream::Qt_6_6);

     // Setting the role to "admin" for AdminManager objects
    role = "admin";

    //This line of code establishes a connection between a signal emitted by a QTcpSocket object....
    //...(socket in this case) and a slot (member function) in the AdminManager class.
    //this: This is a pointer to the receiver object, which is an instance of the AdminManager class...
    //..It's the object that contains the slot to be called when the signal is emitted.
    connect(&socket, &QTcpSocket::connected, this, &AdminManager::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &AdminManager::disconnected);
    connect(&socket, &QTcpSocket::stateChanged, this, &AdminManager::stateChanged);
    connect(&socket, &QTcpSocket::readyRead, this, &AdminManager::readyRead);
    connect(&socket, &QTcpSocket::errorOccurred, this, &AdminManager::error);
}

void AdminManager::viewAccount()
{
    //qDebug()<<"hello from viewAccount client ";
    std::string accountNumber;
    QString accountNumberStr;

    clearScreen();
    qInfo() << "Please Enter the account number";
    std::cin >> accountNumber;
    accountNumberStr = QString::fromStdString(accountNumber);// Convert the account number from std::string to QString
    outStream << accountNumberStr;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qInfo() << "Admin account balance is: " << serverResponse.toInt();
}

void AdminManager::getAccountNumber()
{

    qInfo() << "Please Enter the username:";
    std::string username;
    std::cin >> username;
    QString userName = QString::fromStdString(username);
    outStream << userName;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qInfo() << "Account Number is: " << serverResponse.toString();
    // qDebug()<<"hello from getAccountNumber client ";
}

void AdminManager::viewBankDatabase()
{
    socket.waitForReadyRead(); // Wait until the socket is ready to read

    // Print the bank database from the server response
    // Note the use of noquote() to prevent quoting of the text being printed
    qInfo().noquote() << serverResponse.toString();
}

void AdminManager::createNewUser()
{
    QVariantMap map;  // Declare a QVariantMap to store user information
    std::string username, password;
    QString userName, fullName, flag = "check";
    quint32 age = 0;
    quint16 counter = 0;
    qint32 balance = 0;
    bool ok = false;
    QTextStream cin(stdin);
    requestFlag = "CreateUser";

    do
    {
        if (counter > 0)
        {
            qInfo() << "User name is already existed!!\nPlease Enter a different one:";
            std::cin >> username;
            userName = QString::fromStdString(username);
            outStream << requestFlag << flag << userName;// Send request to server to check username
        }
        else
        {
            qInfo() << "Username:";
            std::cin >> username;
            userName = QString::fromStdString(username);
            outStream << flag << userName;
        }

        counter++;
        socket.waitForReadyRead();
        ok = serverResponse.toBool();
    } while (!ok);

    flag = "update";

    qInfo() << "Full Name:";
    fullName = cin.readLine();

    qInfo() << "Age:";
    std::cin >> age;

    qInfo() << "Balance:";
    std::cin >> balance;

    qInfo() << "Password:";
    std::cin >> password;

    // Send user creation request to server with user information
    map["Fullname"] = fullName;
    map["Age"] = age;
    map["Balance"] = balance;
    map["Username"] = userName;

    QString passwordStr = QString::fromStdString(password);
    outStream << requestFlag << flag << userName << passwordStr << map;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    requestFlag = "General";

    if (serverResponse.toBool() == true)
    {
        qInfo() << "User is created Successfully";
    }
    else
    {
        qInfo() << "User is not created!!";
    }
}

void AdminManager::deleteUser()
{
    qInfo() << "Please send the account number:";
    std::string accountNumber;
    std::cin >> accountNumber;
    QString accountNumberStr = QString::fromStdString(accountNumber);
    outStream << accountNumberStr;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    if (serverResponse.toBool() == true)
    {
        qInfo() << "User is deleted";
    }
    else
    {
        qInfo() << "User is not deleted!!\nAccount number is not existed!!";
    }
}

void AdminManager::updateUser()
{
    QTextStream cin(stdin); // Create a QTextStream to read from standard input
    QString flag = "check";
    QString fullName;
    QVariantMap map; // Declare a QVariantMap to store the updated user information
    QString accountNumberStr;
    std::string accountNumber, password;
    quint16 age = 0;
    quint16 in = 0;// Declare a variable to store the user's choice for updating fields
    std::string key;// Declare a variable to store user input for continuing or exiting update process
    bool chosenFlag = true;// Declare a flag to control the update loop
    qint32 balance = 0;
    quint16 counter = 0;// Declare a counter variable to track attempts
    bool ok = false;// Declare a boolean variable for checking success
    requestFlag = "UpdateUser";// Set the request flag to indicate user update

    // Loop until a valid account number is provided
    do
    {
        if (counter > 0)
        {
            qInfo() << "Account Number is not existed!!\nplease Enter a valid one:";
            std::cin >> accountNumber;
            accountNumberStr = QString::fromStdString(accountNumber);
            outStream << requestFlag << flag << accountNumberStr; // Send request to server to check account number
        }
        else
        {
            qInfo() << "Account Number:";
            std::cin >> accountNumber;
            accountNumberStr = QString::fromStdString(accountNumber);
            outStream << flag << accountNumberStr;
        }
        counter++;
        socket.waitForReadyRead();
        ok = serverResponse.toBool();
    } while (!ok);// Repeat until valid account number is provided

    flag = "update";// Update flag for sending user update request

    // Loop to allow user to update multiple fields
    do
    {
        qInfo() << "Choose the field you want to update:";
        qInfo() << "1-Full Name\n2-Age\n3-Balance\n4-Password";
        std::cin >> in;
        switch (in)
        {
        case 1:
            qInfo() << "New Full Name:";
            fullName = cin.readLine();
            map["Fullname"] = fullName;
            qInfo() << fullName;
            break;
        case 2:
            qInfo() << "New Age:";
            std::cin >> age;
            map["Age"] = age;
            break;
        case 3:
            qInfo() << "New Balance:";
            std::cin >> balance;
            map["Balance"] = balance;
            break;
        case 4:
            qInfo() << "New Password:";
            std::cin >> password;
            map["password"] = QString::fromStdString(password);
            break;
        default:
            qInfo() << "Please enter a valid choice";
            break;
        }
        qInfo() << "----------------------------------------------------------";
        qInfo() << "If you want to update another field press 'y'\nIf you want to save and exit press'n'";
        std::cin >> key;
        if (key != "y")
        {
            chosenFlag = false;
        }
    } while (chosenFlag);// Repeat until user chooses to exit

    outStream << requestFlag << flag << accountNumberStr << map;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    requestFlag = "General";

    if (serverResponse.toBool() == true)
    {
        qInfo() << "User Data is updated Successfully";
    }
    else
    {
        qInfo() << "User Data is not updated!!";
    }
}

void AdminManager::viewTransactionHistory()
{
    qInfo() << "Please send the account number:";
    std::string accountNumber;
    std::cin >> accountNumber;
    QString accountNumberStr = QString::fromStdString(accountNumber);
    qInfo() << "Please send the number of transactions:";
    quint16 count;
    std::cin >> count;
    outStream << accountNumberStr << count;
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qInfo().noquote() << serverResponse.toString();
}

void AdminManager::sendRequestToServer()
{
    outStream << requestFlag << request << role;
}

bool AdminManager::login()
{
    qInfo() << "WELCOME!!";
    qInfo() << "Username: ";
    request = "Login"; // Set request type to login
    outStream << requestFlag << request << role;
    QString adminName, password;
    std::string name;
    std::cin >> name; // Read username from standard input
    adminName = QString::fromStdString(name);
    qInfo() << "Password: ";


    char ch; // Declare a variable to store characters of password
    std::string pass;

    // Loop to read password characters without displaying them
    while (true)
    {
        ch = _getch(); // Read character without echoing to console

        if (ch == 13)// If Enter key is pressed
            break;

        std::cout << '*';// Display '*' instead of characters
        pass += ch;// Append character to password string
    }

    std::cout<< std::endl;
    password = QString::fromStdString(pass);



    bool ok = false; // Declare a boolean variable to track login success


    if (!adminName.isEmpty() && !password.isEmpty())
    {
        outStream << adminName << password;
        socket.waitForBytesWritten();
        socket.waitForReadyRead();
        ok = serverResponse.toBool(); // Check server response for authentication success
        this->adminName = adminName; // Store admin username for future reference

    }

    clearScreen();
    return ok;
}

void AdminManager::start(bool &isLogged)
{
    quint16 input;// Variable to store user input
    char in; // Variable to store additional input
    qInfo() << "Choose from the list:\n1-View Account\n2-View Transaction History\n3-Get Account Number\n4-Create New User"
               "\n5-Update User Data\n6-Delete User\n7-View Bank DataBase\n8-exit";
    std::cin >> input;

    std::cin.ignore(); // Ignore any remaining characters in the input buffer
    clearScreen();
    switch (input)
    {
    case 1:
        request = "View Account";
        sendRequestToServer();
        viewAccount();
        break;
    case 2:
        request = "View Transaction History";
        sendRequestToServer();
        viewTransactionHistory();
        break;
    case 3:
        request = "GetAccNo";
        sendRequestToServer();
        getAccountNumber();
        break;
    case 4:
        request = "Create User";
        sendRequestToServer();
        createNewUser();
        break;
    case 5:
        request = "Update User";
        sendRequestToServer();
        updateUser();
        break;
    case 6:
        request = "Delete User";
        sendRequestToServer();
        deleteUser();
        break;
    case 7:
        request = "View Bank DataBase";
        sendRequestToServer();
        viewBankDatabase();
        break;
    case 8:
        isLogged = false;// Set isLogged to false to indicate logout
        break;
    default:
        qInfo() << "Your choice is invalid";
        break;
    }
    if (input != 8)// If the choice was not to exit
    {
        qInfo() << "if you have another request press 'y' if you want to exit press 'N':";
        std::cin >> in;
        if (in == 'n' || in == 'N')
        {
            isLogged = false;
        }
        clearScreen();
    }
}

void AdminManager::connectToHost(QString host, quint16 port)
{
    // Check if the socket is already open and disconnect if so
    if (socket.isOpen())
        disconnect();
    // Connect the socket to the specified host and port
    socket.connectToHost(host, port);
}

void AdminManager::disconnect()
{
    socket.close();
    socket.waitForDisconnected();
}

//***************************

void AdminManager::connected()
{
    // Create a QTextStream to read from standard input (stdin)
    QTextStream input(stdin, QIODevice::ReadOnly);

    // Read a line of text from standard input, and remove leading and trailing whitespace
    QString userInput = input.readLine().trimmed();

    // Convert the QString to UTF-8 encoded QByteArray and write it to the socket
    socket.write(userInput.toUtf8());
}

void AdminManager::disconnected()
{
    qInfo() << "Disconnected";
}

void AdminManager::error(QAbstractSocket::SocketError socketError)
{
    qInfo() << "Error:" << socketError << socket.errorString();
}

void AdminManager::stateChanged(QAbstractSocket::SocketState socketState)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    QString str = metaEnum.valueToKey(socketState);
}

void AdminManager::readyRead()
{
    if (request == "View Bank DataBase")
    {
        QString database;
        inStream >> database;
        serverResponse.setValue(database);
    }
    else if (request == "View Account")
    {
        quint32 accountMoney;
        inStream >> accountMoney;
        serverResponse.setValue(accountMoney);
    }
    else if (request == "Create User" || (request == "Delete User") || (request == "Update User") || (request == "Login"))
    {
        bool respond;
        inStream >> respond;
        serverResponse.setValue(respond);
    }
    else if (request == "GetAccNo")
    {
        QString accNo;
        inStream >> accNo;
        serverResponse.setValue(accNo);
    }
    else if (request == "View Transaction History")
    {
        QString history;
        inStream >> history;
        serverResponse.setValue(history);
    }
}
