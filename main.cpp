// File Name: main.cpp
//
// Author: Johnathan Edwards
// Date: 12/4/2021
// Assignment Number: 9
// CS3358.003
// Instructor: C Jinshong Hwang
//
// A demonstration of the BinaryTree class

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "BinaryTree.h"
#include "StudentRecord.h"

bool fillStudentRecords(vector<StudentRecord> &);
void displayVector(vector<StudentRecord>);
void vectorToTree(vector<StudentRecord>, BinaryTree &);
void runDemo(vector<StudentRecord>, BinaryTree &);

int main()
{
    vector<StudentRecord> rawList1, rawList2;
    BinaryTree treeList;

    cout << "External file #1:" << endl;
    if (!fillStudentRecords(rawList1))
        return 1;

    cout << endl << "****Demo #1****" << endl << endl;
    runDemo(rawList1, treeList);

    cout << endl << "External file #2:" << endl;
    if(!fillStudentRecords(rawList2))
        return 1;

    cout << endl << "****Demo #2****" << endl << endl;
    runDemo(rawList2, treeList);

    return 0;
}

//*****************************************************************************
// runDemo: a function that demonstrates the use of the BinaryTree class for
// this project
// v: the vector of student records to be passed to the binary tree
// t: the binary tree
// no return
//*****************************************************************************
void runDemo(vector<StudentRecord> v, BinaryTree &t)
{
    char choice;
    string query;

    displayVector(v);
    vectorToTree(v, t);
    t.displayInOrder();

    do
    {
       cout << endl;
       cout << "Enter an ID number to search: ";
       cin >> query;
       t.searchRecord(query);
       cout << endl;
       cout << "Enter an ID number to remove the record: ";
       cin >> query;
       t.removeRecord(query);
       cout << endl;
       cout << "Would you like to do it again? (y or Y: yes, others: no): ";
       cin >> choice;
    }while (choice == 'y' || choice == 'Y');
    cin.clear();
    cin.ignore(1000, '\n');

    cout << endl << endl;
    t.displayInOrder();
    t.~BinaryTree();
}

//*****************************************************************************
// fillStudentRecords: a function that fills a vector with student records from
// an external .txt file
// v: the vector of student records
// return: true if the .txt file is found; false if the .txt file is not found
//*****************************************************************************
bool fillStudentRecords(vector<StudentRecord> &v)
{
    ifstream fin;
    StudentRecord tempRecord;
    string record;

    cout << "Enter a filename (.txt) containing student records: ";
    getline(cin, record);
    cout << endl;

    if (record.find(".txt") == string::npos) //Check filename for ".txt"
        record.append(".txt");

    fin.open(record);

    if (!fin)
    {
        cout << "Student record file could not be found!" << endl;
        return false;
    }

    while (getline(fin, tempRecord.ID, '\t'))
    {
        int *grades = new int[10];
        string tempGrade;

        getline(fin, tempRecord.name, '\t');
        for (int i = 0; i < 9; i++)
        {
            getline(fin, tempGrade, '\t');
            grades[i] = atoi(tempGrade.c_str());
        }
        getline(fin, tempGrade, '\n');
        grades[9] = atoi(tempGrade.c_str());
        tempRecord.testScores = grades;
        v.push_back(tempRecord);
    }

    fin.close();
    return true;
}

//*****************************************************************************
// displayVector: a function that displays a vector of student records
// v: the vector of student records
// no return
//*****************************************************************************
void displayVector(vector<StudentRecord> v)
{
    cout << "The vector containing student records:" << endl << endl;
    for(int x = 0; x < v.size(); x++)
    {
        cout << "ID: " << v[x].ID;
        cout << " Name: " << v[x].name << endl;
        cout << "    Test Grades: ";
        for (int i = 0; i < 10; i++)
        {
            if (i < 9)
                cout << v[x].testScores[i] << ", ";
            else
                cout << v[x].testScores[i] << endl;
        }
        cout << endl;
    }

    cout << endl << endl;
}

//*****************************************************************************
// vectorToTree: a function that passes all of the records from a vector to a
// binary tree
// v: the vector of student records
// t: the binary tree of student records
// no return
//*****************************************************************************
void vectorToTree(vector<StudentRecord> v, BinaryTree &t)
{
    for (int i = 0; i < v.size(); i++)
    {
        t.insertRecord(v[i]);
    }
}
