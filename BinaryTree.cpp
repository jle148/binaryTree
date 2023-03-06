// File Name: BinaryTree.cpp
//
// Author: Johnathan Edwards
// Date: 12/4/2021
// Assignment Number: 9
// CS3358.003
// Instructor: C Jinshong Hwang
//
// Definitions of the member functions of the BinaryTree class.

#include <string>
#include <iostream>

using namespace std;

#include "StudentRecord.h"
#include "Binarytree.h"

//*****************************************************************************
// BinaryTree: BinaryTree constructor that sets the root pointer to nullptr
//*****************************************************************************
BinaryTree::BinaryTree()
{
    root = nullptr;
}

//*****************************************************************************
// ~BinaryTree: BinaryTree destructor
//*****************************************************************************
BinaryTree::~BinaryTree()
{
    destroySubTree(root);
    root = nullptr;
}

//*****************************************************************************
// displayInOrder: the private class function that displays the binary tree
// using an in-order traversal with a recursive function
// nodePtr: the pointer used to traverse the tree
// no return
//*****************************************************************************
void BinaryTree::displayInOrder(LeafNode *nodePtr) const
{
    if (nodePtr)
    {
        displayInOrder(nodePtr->left);
        cout << "ID: " << nodePtr->record.ID;
        cout << " Name: " << nodePtr->record.name << endl;
        cout << "    Test Grades: ";
        for (int i = 0; i < 10; i++)
        {
            if (i < 9)
                cout << nodePtr->record.testScores[i] << ", ";
            else
                cout << nodePtr->record.testScores[i] << endl << endl;
        }
        displayInOrder(nodePtr->right);
    }
}

//*****************************************************************************
// displayInOrder: the public class function that calls the private
// displayInOrder class function
// no return
//*****************************************************************************
void BinaryTree::displayInOrder() const
{
    cout << "The binary tree displayed in order: " << endl << endl;
    displayInOrder(root);
}

//*****************************************************************************
// insertRecord: the public class function used to insert a new record to the
// binary tree. it calls the private function insertLeaf to do so
// r: the record
// no return
//*****************************************************************************
void BinaryTree::insertRecord(StudentRecord r)
{
    LeafNode *newNode = new LeafNode;

    newNode->record = r;
    newNode->left = nullptr;
    newNode->right = nullptr;

    insertLeaf(root, newNode);
}

//*****************************************************************************
// insertLeaf: the private class function that inserts a new node to the binary
// tree
// nodePtr: the pointer that traverses the binary tree
// newNode: the node to be inserted
// no return
//*****************************************************************************
void BinaryTree::insertLeaf(LeafNode *&nodePtr, LeafNode *&newNode)
{
    if (nodePtr == nullptr)
        nodePtr = newNode;
    else if (newNode->record.ID < nodePtr->record.ID)
        insertLeaf(nodePtr->left, newNode);
    else
        insertLeaf(nodePtr->right, newNode);
}

//*****************************************************************************
// searchRecord: the public class function that allows the user to search for
// a student record by student ID
// query: the student ID to be searched
// return: true if a record is found; false if a record is not found
//*****************************************************************************
bool BinaryTree::searchRecord(string query)
{
    LeafNode *nodePtr = root;

    cout << endl << "Searching for record \"" << query << "\"..." << endl;

    while(nodePtr)
    {
        if (nodePtr->record.ID == query)
        {
            cout << "Record found:" << endl;
            cout << "ID: " << nodePtr->record.ID;
            cout << " Name: " << nodePtr->record.name << endl;
            return true;
        }
        else if(query < nodePtr->record.ID)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }

    cout << endl << "Record not found!" << endl;
    return false;
}

//*****************************************************************************
// removeRecord: the public class function that allows the user to remove a
// student record by student ID. it calls the private deleteNode class function
// query: the student ID whose record will be removed
// no return
//*****************************************************************************
void BinaryTree::removeRecord(string query)
{
    cout << endl << "Removing record \"" << query << "\"..." << endl;
    deleteNode(query, root);
}

//*****************************************************************************
// deleteNode: the private class function that finds the node to be deleted
// recursively and calls the makeDeletion private class function
// num: the student ID to be searched
// nodePtr: the pointer that traverses the tree
// no return
//*****************************************************************************
void BinaryTree::deleteNode(string num, LeafNode *&nodePtr)
{
    if (nodePtr == nullptr)
    {
        cout << "Record not found!" << endl;
        return;
    }
    else if (num < nodePtr->record.ID)
        deleteNode(num, nodePtr->left);
    else if (num > nodePtr->record.ID)
        deleteNode(num, nodePtr->right);
    else
        makeDeletion(nodePtr);
}

//*****************************************************************************
// makeDeletion: the private class function that reconnects the tree and
// deletes the node that was searched for in the deleteNode function
// nodePtr: the location in the tree to be deleted
// no return
//*****************************************************************************
void BinaryTree::makeDeletion(LeafNode *&nodePtr)
{
    LeafNode *tempPtr = nullptr;

    if (nodePtr == nullptr)
        cout << "Cannot delete empty node." << endl;
    else if (nodePtr->right == nullptr)
    {
        tempPtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempPtr;
    }
    else if (nodePtr->left == nullptr)
    {
        tempPtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempPtr;
    }
    else
    {
        tempPtr = nodePtr->right;

        while (tempPtr->left)
            tempPtr = tempPtr->left;

        tempPtr->left = nodePtr->left;
        tempPtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempPtr;
    }
}

//*****************************************************************************
// destroySubTree: the private class function that removes all nodes below the
// node in the function call including the node itself. it is called by the
// ~BinaryTree function
// nodePtr: the pointer to the node who will be deleted along with its subtree
// no return
//*****************************************************************************
void BinaryTree::destroySubTree(LeafNode *nodePtr)
{
    if (nodePtr)
    {
        if (nodePtr->left)
            destroySubTree(nodePtr->left);
        if (nodePtr->right)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }

}
