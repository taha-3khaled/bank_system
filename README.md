# bank_system
bank_system using the client server model.
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




