# bank_system
bank_system using the client server model.
## server
1. Server Class (server.h, server.cpp):
* The Server class is derived from DataBase, which suggests that it has access to a database for handling banking-related operations.
* It listens for incoming connections (start method) and handles new connections in the newConnection slot.
* It has slots for handling disconnections (disconnected) and incoming data (readyRead).
* The Handlerequest method processes incoming requests based on the user's role (admin or user) and the type of request.
* The server communicates with clients using JSON messages over TCP/IP.

2. Database Class (database.h, database.cpp):
* The DataBase class handles interactions with the database, including user authentication, account balance retrieval, transactions, and user management.
* It utilizes Qt's JSON support to read and write data in JSON format.
* Methods like CheckLogin, ViewAccBalance, TransferAmount, MakeTransaction, SaveTransaction, etc., perform various banking operations.

3. Main Function (main.cpp):
* The main function initializes the server and starts it, allowing it to listen for incoming connections.

## Client  
*1. Main Program (main.cpp):*
*Entry point of the application.
* Handles user input to determine whether the user is a regular user or an admin.
* Instantiates UserManager or AdminManager based on user input.
* Manages the login process and user interactions.
* Exits the application when the user chooses to exit.


 *2. Client Class (client.h, client.cpp):*
* Base class for UserManager and AdminManager.
* Defines pure virtual functions for handling account-related operations such as
  *  getting the account number.
  *  viewing account details.
  *  viewing transaction history.
  *  sending requests to the server.
  *  performing login.
* Contains a method to clear the console screen.

*3. UserManager Class (user.h, user.cpp):*
* Inherits from Client class.
* Implements user-specific functionalities such as:
  *  transferring accounts.
  *  making transactions.
  *  viewing account details.
  *  viewing transaction history.
  *  logging in.
* Manages the client-side communication with the server.

*4. AdminManager Class (admin.h, admin.cpp):*
* Inherits from Client class.
* Implements admin-specific functionalities such as :
  * viewing account details
  * getting account numbers
  * viewing bank database
  * creating new users
  * deleting users
  * updating user data
  * viewing transaction history
  * logging in.
* Manages the client-side communication with the server.




