# Student-DBMS
A basic database management system for students.


This program is a simple student database management system that stores the students name, ID, and GPA. The database can be ordered by name or by ID.
It has the following operations: 

*Create Database:* Use this operation first to create a database and choose if you will order by name or ID. To add further data to the database use the Insert Data operation.

*Insert/Delete/Search:* Use these operations to insert, delete, or find a student in the database.

*Print:* Use this operation to print the database to your console window.

*Save:* Using this operation you can save your database to the a file named database.txt. Make sure the file database.txt exists in your directory before using this operation.


The DBMS has been implemented in C++ as a doubly linked list. It has the following files:
*main.cpp:* Contains the main() and other helper functions.
*node.h:* Contains the definition of data type studentData and the definition of the node for the database linked list.
*database.h:* Header file for the database linked list.
*database.cpp:* Implementation file for the database linked list. 
