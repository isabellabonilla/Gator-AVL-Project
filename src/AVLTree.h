// Author: Isabella Bonilla
#include <iostream>
#include <vector>
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
using namespace std;

class AVLTree {
private:
    struct StudentNode {
        string name;
        int gatorID;
        int height;
        StudentNode *left;
        StudentNode *right;
        StudentNode(string name, int val);
    };

    StudentNode *root; // root of AVL tree

    static int getHeight(StudentNode *node); // calculate height of node (helper function)
    int getBalanceFactor(StudentNode *node); // calculate balance factor of node (helper function)
    StudentNode *getInorderSuccessor(StudentNode *node); // get inorder successor of node (helper function)

    StudentNode *rightRotation(StudentNode *subtreeRoot); // balance: right rotation
    StudentNode *leftRotation(StudentNode *subtreeRoot); // balance: left rotation

    void deleteTree(StudentNode *node); // delete tree with postorder traversal (helper recursive function)

    StudentNode *insertHelper(StudentNode *node, string& newName, int newGatorID, bool& duplicate); // add node to tree (recursive helper function)
    StudentNode *searchIDHelper(StudentNode *node, int targetID); // search for specific gator ID in tree (recursive helper function)
    void searchNameHelper(StudentNode *node, string& targetName, vector<int>& found); // search for name in tree (recursive helper function)
    StudentNode *removeHelper(StudentNode *node, int targetID); // remove node with specified targetID from tree (recursive helper function)
    int removeInorderHelper(StudentNode *node, int &count, int n); // find inorder traversed nth node gatorID (recursive helper function)

    void inorder(StudentNode *node, vector<string> &names); // inorder traverse tree (recursive helper function)
    void preorder(StudentNode *node, vector<string> &names); // preorder traverse tree (recursive helper function)
    void postorder(StudentNode *node, vector<string> &names); // postorder traverse tree (recursive helper function)

    bool validateName(const string& name); // ensure gatorID follows constraints (helper function)
    bool validateID(const string& strGatorID); // ensure name follows constraints (helper function)

public:
    AVLTree(); // tree constructor
    ~AVLTree(); // tree destructor

    void insert(const string& newName, const string& strNewGatorID, ostream& os = cout);  // insert new student node to tree, print whether successful
    void searchID(const string& strTargetID, ostream& os = cout); // search for targetID and print whether it was found
    void searchName(const string& targetName, ostream& os = cout); // search for targetName and print all associated gatorID, else print unsuccessful
    void remove(const string& strTargetID, ostream& os = cout); // print whether the account with the targetID is removed
    void printInorder(ostream& os = cout); // print comma separated inorder traversal of the names in the tree
    void printPreorder(ostream& os = cout); // print comma separated preorder traversal of the names in the tree
    void printPostorder(ostream& os = cout); // print comma separated postorder traversal of the names in the tree
    void printLevelCount(ostream& os = cout); // print number of levels in the tree
    void removeInorder(int n, ostream& os = cout); // remove nth gatorID from inorder traversal of the tree
};

#endif //PROJECT1_AVL_H
