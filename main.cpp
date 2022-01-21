#include <limits>
#include "database.h"

/*-----function declarations----*/

//displays start menu when the program is run
void startMenu(); 

//takes user input where required and checks them based on the number i passed to the function. 
//if i = 1: takes user input and checks that input is either number 1 or 2. 
//if i = 2: takes user input and checks that input is between 1 and 8 inclusive. 
//gives error if wrong input and waits for new input
//if correct input then the function returns it
int checkInput(int i); 

//asks user if they want to use another operation
int nextOperation();

//instructions on how to use the program
void help();

/*--------------------------------*/


int main() {
    startMenu();  //Display start menu
    database sdbms;
    int numOperation;   //Operation number user chooses from the menu
    double GPA; string name, ID;
    bool orderByID;

    cout << "Input a number from 1 to 8 to choose from the above operations: ";
    numOperation = checkInput(2);

    while (1){
        switch (numOperation){

            //User chooses operation 1 to create database 
            case 1:{
                system("CLS");  //clear console
                cout << "You input 1. To create a database please enter the Name, ID and GPA of the first student:" << endl;
                
                //prompting user to input name and validating it
                cout << "Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //flushing cin buffer
                getline(cin, name);
                while (name[0] < 65 or name[0] > 122){
                    cout << "Please enter a valid name: ";
                    getline(cin, name);
                }

                //prompting user to input ID
                cout << "ID: ";
                getline(cin, ID);

                //prompting user to input GPA and validating it
                cout << "GPA: ";
                while (!(cin >> GPA) || GPA > 4 || GPA < 0){
                    cin.clear();
                    while (cin.get() != '\n') continue;
                    cout << "Please enter a valid GPA: ";
                }

                cout << "How do you want to order the database? Input 1 to order it by name or 2 to order it by ID.\n"
                    << "1-Name     2-ID\n";
                orderByID = checkInput(1) - 1;

                //Database created
                sdbms.createDatabase(orderByID, name, ID, GPA);
                        
                numOperation = nextOperation();
                break;
            }

            //User chooses option 2 to insert data
            case 2:{
                system("CLS");
                cout << "You input 2. Please enter number of students you want to enter data for: ";

                bool insertSuccess = 1; //to check whether student was successfully inserted
                
                int numStudents = checkInput(0);

                for (int i = 1; i <= numStudents; i++)
                {
                    if (insertSuccess)
                    {
                        cout << "Please enter the Name, ID and GPA of student number " << i <<": " << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, name);
                        while ( name[0] < 65 or name[0] > 122){
                            cout << "Please enter a valid name: ";
                            getline(cin, name);
                        }

                        getline(cin, ID);

                        while (!(cin >> GPA) || GPA > 4 || GPA < 0){
                            cin.clear();
                            while (cin.get() != '\n') continue;
                            cout << "Please enter a valid GPA: ";
                        }

                        insertSuccess = sdbms.insertStudent(name, ID, GPA);
                    }
                }
                
                numOperation = nextOperation();
                break;
            }

            //User chooses option 3 to delete data
            case 3:{
                system("CLS");
                cout << "You input 3. Please enter number of students you want to delete from the database: ";
                int statusDelete = 1;
                
                int numDelete = checkInput(0);
                
                for (int k = 1 ; k <= numDelete; k++){
                    if (statusDelete != 0){
                        cout << "Please enter the ID of student you want to delete: ";
                        
                        getline(cin , ID);
                        statusDelete = sdbms.deleteStudent(ID);
                        if (statusDelete == 1) cout << "Student with ID " << ID << " successfully deleted from the database.\n\n";
                        if (statusDelete == 2) k--; //ID not found
                    }
                }

                numOperation = nextOperation();
                break;
            }

            //User chooses 5 to search the database
            case 4:{
                system("CLS");
                int statusSearch = 1;
                cout << "You input 4. Please enter number of students you want to search in the database: ";
                
                int numSearch = checkInput(0);
                
                for ( int l = 1 ; l <= numSearch ; l++){
                    if (statusSearch != 0) {
                        cout << "Please enter ID of the student you want to search: ";
                        
                        getline(cin , ID);
                        statusSearch = sdbms.searchStudent(ID);
                        if (statusSearch == 2) l--;   //ID not found
                    }
                }

                numOperation = nextOperation();
                break;
            }

            //User chooese 5 to print database
            case 5:{
                system("CLS");
                sdbms.printDatabase();
                numOperation = nextOperation();
                break;
            }

            //User chooses 6 to save database to file
            case 6:{
                system("CLS");
                sdbms.savetoFile();
                numOperation = nextOperation();
                break;
            }

            //User chooses 7 for help
            case 7:{
                help();
                numOperation = nextOperation();
                break;
            }
            
            //User chooses 8 to exit program
            case 8:{
                exit(EXIT_SUCCESS);
                break ;
            }
        }
    }
    


}

/*-----function definitions----*/

void startMenu(){
    cout <<"\n------STUDENT DATABASE MANAGEMENT SYSTEM------\n\n";

    cout << "  1- Create Database\n"
         << "  2- Insert Data\n"
         << "  3- Delete Data\n"
         << "  4- Search on Data\n"
         << "  5- Print Data\n"
         << "  6- Save\n"
         << "  7- Help\n"
         << "  8- Exit\n"
         << "\n\n";
}

int checkInput(int i){
    int numIn;  //to store user input

    switch (i){

        //to check that user inputs either 1 or 2
        case 1:{
            while (!(cin >> numIn) ||  numIn > 2 || numIn < 1){
            cin.clear();
            while ( cin.get() != '\n') continue;
            cout << "Invalid Input! Please try again: ";
            }
            break;
        }

        //to check that the user inputs number from 1 to 8
        case 2:{
            while (!(cin >> numIn) ||  numIn > 8 || numIn < 1){
            cin.clear();
            while ( cin.get() != '\n') continue;
            cout << "Invalid Input! Please try again: ";
            }
            break;
        }

        //to check that user inputs a number greater than 0    
        default:{
            while (!(cin >> numIn) || numIn < 1){
            cin.clear();
            while ( cin.get() != '\n') continue;
            cout << "Invalid Input! Please try again: ";
            }
            break;
        }      
    }
    
    return numIn; //return the user input
}

int nextOperation(){
    int numOperation;   //to store what operation user wants to use

    cout << "\n\nDo you want to use another operation? Input 1 for yes or 2 to terminate program.\n"
         << "1- Yes   2- No \n";
    int userInput = checkInput(1);
    
    //user wants to use another operation
    if (userInput == 1){
        system("CLS");
        startMenu();
        cout << "Input a number from 1 to 8 to choose from the above operations: ";
        numOperation = checkInput(2);
        return numOperation;
    }
    
    //user wants to terminate program
    else return 8;
}

void help(){
    system("CLS");
    //instructions on how to use the program
    cout << "This program is a simple student database management system that stores the students name, ID, and GPA. The database can be ordered by name or by ID.\n\n\n"
         << "*It has the following operations*\n\n"
         << "Create Database: Use this operation first to create a database and choose if you will order by name or ID. To add further data to the database use the Insert Data operation.\n\n"
         << "Insert/Delete/Search: Use these operations to insert, delete, or find a student in the database.\n\n"
         << "Print: Use this operation to print the database to your console window.\n\n"
         << "Save: Using this operation you can save your database to the a file named database.txt. Make sure the file database.txt exists in your directory before using this operation." << endl;
}