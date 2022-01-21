#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
//#include <cctype>
//#include <conio.h>
//#include <stdlib.h>

using namespace std;


struct studentData  //datatype to store student information
{
    string name;
    string ID;
    double GPA;
};

struct node     //node of the database linked list used to store the students
{
   studentData data;
   node * next;
   node * back;
};









#endif 