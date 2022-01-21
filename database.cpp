#include <fstream>
#include "database.h"

//implementation of database class member functions

database::database(){
    firstNode = NULL;
    lastNode = NULL;
}

int database::createDatabase(bool orderByID, string name, string ID, double GPA){
    
    if(firstNode == NULL) {     //adding first student node to the database linked list
        this->orderByID = orderByID;
      
        tempNode = new node;
        tempNode->data.name = name;
        tempNode->data.ID = ID;
        tempNode->data.GPA = GPA;
        tempNode->next = NULL;
        tempNode->back = NULL;
        
        firstNode = tempNode;
        lastNode = tempNode;
        
        return 1;
    }

    else {
        cout << "A database has been previously created using the create database option" << endl;
        return 0;      
    }

}

int database::insertStudent(string name, string ID, double GPA){
    //creating a new node for to add a student to the database linked list
    tempNode = new node;
    tempNode->data.name = name;
    tempNode->data.ID = ID;
    tempNode->data.GPA = GPA;    

    if (firstNode != NULL){      //to check if database created using create option
        
        //if database is ordered by ID
        if (orderByID){     

            //student ID smaller than equal to the first student
            //student added to the top of the database linked list
            if (firstNode->data.ID >= ID){      
                firstNode->back = tempNode;
                tempNode->next = firstNode;
                tempNode->back = NULL;
                firstNode = tempNode;
                return 1;
            }

            //student ID greater than equal to the last student
            //student added to the end of the database linked list
            else if (lastNode->data.ID <= ID){     
                lastNode->next = tempNode;
                tempNode->next = NULL;
                tempNode->back = lastNode;
                lastNode = tempNode;
                return 1;
            }
            
            //database searched and student inserted into the database according to the ID
            else {
                node* curr = firstNode;
                node* currNext = firstNode->next;

                while (currNext->next != NULL){     //find postion for the student in the database linked list
                    curr = curr->next;
                    currNext = currNext->next;
                    if (currNext->data.ID >= ID) break;
                }
                
                //insert the new student node into the database linked list
                currNext->back = tempNode;
                tempNode->next = currNext;
                tempNode->back = curr;
                curr->next = tempNode;
                return 1;
            }

        }

        //if database is ordered by name
        else {

            //student name smaller than equal to the first student
            //student added to the top of the database linked list
            if (firstNode->data.name >= name) {
                firstNode->back = tempNode;
                tempNode->next = firstNode;
                tempNode->back = NULL;
                firstNode = tempNode;
                return 1;
            }

            //student name greater than equal to the last student
            //student added to the end of the database linked list
            else if (lastNode->data.name <= name) {
                lastNode->next = tempNode;
                tempNode->next = NULL;
                tempNode->back = lastNode;
                lastNode = tempNode;
                return 1;
            }

            //database searched and student inserted into the database according to the name
            else {
                node* curr = firstNode;
                node* currNext = firstNode->next;

                while (currNext->next != NULL){     //find postion for the student in the database linked list
                    curr = curr->next;
                    currNext = currNext->next;
                    if (currNext->data.name >= name) break;
                }
                
                //insert the new student node into the database linked list
                currNext->back = tempNode;
                tempNode->next = currNext;
                tempNode->back = curr;
                curr->next = tempNode;
                return 1;
            }            
        }                
        
        
    }

    else{      //if database not created
        delete tempNode;
        cout << "Please create a database first using the create option" << endl;
        return 0;
    }
}

int database::deleteStudent(string ID){
    bool idExists = false; //used to check if ID exists in the database

    if (firstNode != NULL) {    //check that database not empty
        node* delFirst = firstNode;
        node* delLast = lastNode;
        node* delNext = firstNode->next;
        node* delBack = lastNode->back;

        //ID same as first student
        //first student node deleted from database linked list
        if (firstNode->data.ID == ID) {
            firstNode = delNext;
            firstNode->back = NULL;
            delete (delFirst);
            return 1;
        }

        //ID same as last student
        //last student node deleted from database linked list
        else if (lastNode->data.ID == ID) {
            lastNode = delBack;
            lastNode->next = NULL ;
            delete (delLast);
            return 1;
        }

        //search the whole linked list for ID and delete it
        else {
            while (delFirst->next != NULL) {
                delFirst = delFirst->next ;
                delBack = delFirst->back ;
                delNext = delFirst->next ;

                if (ID == delFirst->data.ID) {  //if ID found then we delete the corresponding node
                    delNext->back = delFirst->back ;
                    delBack->next = delFirst->next;
                    delete (delFirst);
                    idExists = true;
                    return 1;
                }
            }
        }

        //ID doesnt exist in database
        if (!idExists) {
            cout << "The ID entered doesnot exist in the database" << endl;
            return 2;
        }
    }
    
    else {      //database empty
        cout << "The database is empty" << endl;
        return 0;
    }
}

void database::printDatabase(){
    cout << "******Student Database Management System*******\n\n";
    int counter = 1;
    node *printNode = firstNode;
    while (printNode != NULL)
    {
        cout <<counter<<"-  Name: "<< printNode->data.name << ", ID: " << printNode->data.ID << ", GPA: " << printNode->data.GPA << endl;
        printNode = printNode->next ;
        counter++;
    }
}

int database::savetoFile(){
    node *temp = firstNode;
    int counter = 1;
    bool dbEmpty = true; //check if database empty
    ofstream fo("database.txt");   

    //error in opening file
    if (!fo.is_open()){
        cout << "The file database.txt could not be opened. Make sure a text file named database.txt exists in the directory" << endl;
        return 0;
    }

    //writing the database in the file
    fo << "******Student Database Management System*******\n\n";
    while (temp != NULL)
    {   
        fo <<counter<<"-  Name: "<< temp->data.name << ", ID: " << temp->data.ID << ", GPA: " << temp->data.GPA << endl;
        temp = temp->next;
        counter++;
        dbEmpty = false;
    }
    fo.close();

    //database is empty
    if (dbEmpty){
        cout << "Database is empty. Nothing to save to the file" << endl;
        return 0;
    }
    
    //database succesfully written to file
    else{
        cout << "Database has been saved in the file database.txt" << endl;
        return 1;
    }
    
}

int database::searchStudent(string ID){
    node *temp = firstNode;
    
    if (temp == NULL){  //database empty
        cout << "Database is empty." << endl;
        return 0;
    }

    else{     //database not empty
        while (temp != NULL){
            if (temp->data.ID == ID){
                cout << "Name: " <<temp->data.name << "    ID: " <<temp->data.ID <<"    GPA: " <<temp->data.GPA << endl;
                return 1;
            }
            temp = temp->next;
        }
        
        //ID doesnot exist
        cout << "The given ID doesnot exist in the database." << endl;
        return 2;
    }
}
