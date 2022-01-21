#ifndef DATABASE_H
#define DATABASE_H

#include "node.h"

class database      //class to store students data as a doubly linked list
{
private:

    node *firstNode , *lastNode , *tempNode;
    bool orderByID; //to store if database will be ordered by name (orderBy = 0/FALSE) or by ID (orderType = 1/TRUE)

public:

    //default constructor
    database();


    //create the student database by adding the first student to the database
    //returns 1 if database succesfully created. returns 0 with error message if database already created 
    int createDatabase(bool orderByID, string name, string ID, double GPA);


    //add a student to the database created using createDatabase()
    //returns 1 if success. returns 0 and prints error message, if no database exists to add student to 
    int insertStudent(string name, string ID, double GPA);  
    

    //delete a student from the database with the given ID
    //returns 0 and prints error msg if database empty. returns 1 if successfully deleted. returns 2 and prints error msg if ID doesnt exist 
    int deleteStudent(string ID);   
    

    //print the database on the console
    void printDatabase();   
    

    //save the database in a file named "database.txt"
    //returns 1 if success. returns 0 and the relevant error msg if file database.txt doesnt exist in the directory or databse is empty
    int savetoFile();   
   

    //find a student with the given ID
    //returns 0 and prints error msg if database empty. returns 1 and prints student details if ID found. returns 2 and error msg if ID not found
    int searchStudent(string ID);   
      

};


#endif