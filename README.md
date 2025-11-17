# Project-3-Bank-System-My-Solution
This is project 3 at course 7 from road map with Programming Advices .


📌 Notes

The system is designed for learning file handling and data management in C++.

No database is used — everything is managed through text-file storage.

Perfect for beginners wanting to understand CRUD operations and file I/O.




Bank Management System (C++ Console Application)

This project is a Bank Management System built in C++, designed to manage client information through a simple and intuitive console-based interface.
The system uses file handling, structs, and vector containers to store, update, and retrieve client data efficiently.

The program allows bank employees to manage clients using several operations such as adding, deleting, updating, and searching for accounts.
All data is stored in a text file (Clients Data.txt) using a custom serialization format.

✨ Features
1. Show All Clients

Displays a formatted table of all stored clients including:

Account Number

PIN

Name

Phone

Account Balance

2. Add New Client

Allows the user to enter:

Account number

PIN code

Full name

Phone number

Initial balance

New clients are appended directly into the database file.

3. Delete Client

Search for a client using account number

Displays full client card before deleting

Asks for confirmation before removal

Uses a soft-delete mechanism with a marking flag

Saves the updated list into the file

4. Update Client Information

Edit client name, phone, PIN, and balance

Shows old data first

Saves modifications to the file

5. Find Client

Retrieve and display a single client's full details.

6. Persistent Storage

All operations are saved in "Clients Data.txt" using a clear structured format




🛠️ Technical Concepts Used

C++ Structs

Enums

File Handling (fstream)

Vector Container

String splitting & parsing

Serialization & Deserialization

Modular function-based architecture

Console UI

Safe input handling

CRUD operations
