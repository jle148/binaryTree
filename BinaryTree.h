// File Name: BinaryTree.h
//
// Author: Johnathan Edwards
// Date: 12/4/2021
// Assignment Number: 9
// CS3358.003
// Instructor: C Jinshong Hwang
//
// Definition of the BinaryTree class

#include <iostream>
#include <string>

using namespace std;

#include "StudentRecord.h"

class BinaryTree
{
private:
    struct LeafNode
    {
        StudentRecord record;
        LeafNode *right;
        LeafNode *left;
    };
    LeafNode *root;

    void insertLeaf(LeafNode *&, LeafNode *&);
    void destroySubTree(LeafNode *);
    void deleteNode(string, LeafNode *&);
    void makeDeletion(LeafNode *&);
    void displayInOrder(LeafNode *) const;

public:
    BinaryTree();
    ~BinaryTree();

    void insertRecord(StudentRecord);
    bool searchRecord(string);
    void removeRecord(string);
    void displayInOrder() const;
};
