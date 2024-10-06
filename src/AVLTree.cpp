// Author: Isabella Bonilla
#include "AVLTree.h"
#include <vector>
using namespace std;

AVLTree::StudentNode::StudentNode(string name, int gatorID) { // powerpoint: balanced Trees - Slide 26
    this->name = name;
    this->gatorID = gatorID;
    height = 1;
    right = nullptr;
    left = nullptr;
}

int AVLTree::getHeight(AVLTree::StudentNode *node) {
    if(node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(AVLTree::StudentNode *node) {
    if(node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVLTree::StudentNode *AVLTree::rightRotation(AVLTree::StudentNode *subtreeRoot) { // module 5: stepik solutions 5.1b
    StudentNode *newRoot = subtreeRoot->left; // reassign local root
    StudentNode *rightSubtree = newRoot->right;

    // rotation
    newRoot->right = subtreeRoot;
    subtreeRoot->left = rightSubtree;

    // height update
    subtreeRoot->height = 1 + max(getHeight(subtreeRoot->left),getHeight(subtreeRoot->right));
    newRoot->height = 1 + max(getHeight(newRoot->left),getHeight(newRoot->right));

    return newRoot;
}

AVLTree::StudentNode *AVLTree::leftRotation(AVLTree::StudentNode *subtreeRoot) { // module 5: stepik solutions 5.1b
    StudentNode *newRoot = subtreeRoot->right; // reassign local root
    StudentNode *leftSubtree = newRoot->left;

    // rotation
    newRoot->left = subtreeRoot;
    subtreeRoot->right = leftSubtree;

    // update height
    subtreeRoot->height = 1 + max(getHeight(subtreeRoot->left),getHeight(subtreeRoot->right));
    newRoot->height = 1 + max(getHeight(newRoot->left),getHeight(newRoot->right));

    return newRoot;
}

AVLTree::AVLTree() {
    this->root = nullptr;
}

AVLTree::~AVLTree() {
    deleteTree(this->root);
}

void AVLTree::deleteTree(AVLTree::StudentNode *node) { // delete tree recursively with post-order traversal
    if(node == nullptr) { // base case
        return;
    }

    deleteTree(node->left); // delete left subtree
    deleteTree(node->right); // delete right subtree
    delete node; // delete current node
}

// powerpoint: balanced trees - slide 28
AVLTree::StudentNode *AVLTree::insertHelper(AVLTree::StudentNode *node, string& newName, int newGatorID, bool& duplicate) {
    if(node == nullptr) { // base case
        return new StudentNode(newName, newGatorID);
    }

    if (newGatorID == node->gatorID) { // check if gatorID is unique
        duplicate = true; // there is a duplicate
        return node;
    }
    else if (newGatorID < node->gatorID) { // if new gatorID is less than the root's gatorId, sort to left subtree
        node->left = insertHelper(node->left, newName, newGatorID, duplicate);
    }
    else if (newGatorID > node->gatorID) { // if new gatorID is greater than the root's gatorId, sort to right subtree
        node->right = insertHelper(node->right, newName, newGatorID, duplicate);
    }

    // update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    //balance tree accordingly
    int balanceFactor = getBalanceFactor(node);

    if(balanceFactor > 1 && newGatorID < node->left->gatorID) { // LL case alignment
        return rightRotation(node);
    }
    else if (balanceFactor < -1 && newGatorID > node->right->gatorID) { // RR case alignment
        return leftRotation(node);
    }
    else if (balanceFactor > 1 && newGatorID > node->left->gatorID) { // LR case alignment
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    else if (balanceFactor < -1 && newGatorID < node->right->gatorID) { //RL case alignment
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    // balance factor of {-1, 0, 1}
    return node;
}

void AVLTree::insert(const string& newName, const string& strNewGatorID, ostream& os) {
    if(validateName(newName) && validateID(strNewGatorID)) { // if valid ID and name
        int newGatorID = stoi(strNewGatorID); // convert name to int
        bool duplicate = false;

        StudentNode *newRoot = insertHelper(this->root, const_cast<string &>(newName), newGatorID, duplicate);

        if(duplicate) { // if gatorID is a duplicate, insertion is unsuccessful
            os << "unsuccessful" << endl;
        }
        else { // if unique gatorID is successfully inserted
            this->root = newRoot; // update root in case of tree balancing
            os << "successful" << endl;
        }
    }
    else { // if invalid ID or name
        os << "unsuccessful" << endl;
    }

}

AVLTree::StudentNode *AVLTree::searchIDHelper(AVLTree::StudentNode *node, int targetID) {
    if(node == nullptr) { // base case
        return nullptr;
    }
    else if(targetID == node->gatorID) { // if target ID is found, return specific node
        return node;
    }
    else if(targetID > node->gatorID) { // if targetID is greater than current gatorID, traverse right child
        return searchIDHelper(node->right, targetID);
    }
    else if (targetID < node->gatorID) { // if target is less than current gatorID, traverse left child
        return searchIDHelper(node->left, targetID);
    }

    return nullptr;
}

void AVLTree::searchID(const string& strTargetID, ostream& os) {
    if(validateID(strTargetID)) { // if valid ID
        int targetID = stoi(strTargetID); // convert name to int
        StudentNode* targetNode = searchIDHelper(this->root, targetID);

        if(targetNode == nullptr) { // if gatorID doesn't exist within the tree
            os << "unsuccessful" << endl;
        }
        else { // if gatorID was found, print the name
            os << targetNode->name << endl;
        }
    }
    else { // invalid ID
        os << "unsuccessful" << endl;
    }
}

void AVLTree::searchNameHelper(AVLTree::StudentNode *node, string &targetName, vector<int> &found) {
    if(node == nullptr) { // base case
        return;
    }

    if (targetName == node->name) { // if name is found, add gatorID to vector
        found.push_back(node->gatorID);
    }

     // pre-order traversal
    searchNameHelper(node->left, targetName, found);
    searchNameHelper(node->right, targetName, found);
}

void AVLTree::searchName(const string &targetName, ostream& os) {
    if(validateName(targetName)) { // if valid name
        vector<int> found;
        searchNameHelper(this->root, const_cast<string &>(targetName), found);

        if(found.empty()) { // if name doesn't exist within the tree
            os << "unsuccessful" << endl;
        }
        else {
            for(int gatorID : found) { // if name was found, print all associated gator ID of name
                os << gatorID << endl;
            }
        }
    }
    else { // invalid name
        os << "unsuccessful" << endl;
    }
}

void AVLTree::remove(const string& strTargetID, ostream& os) { // powerpoint: balanced trees - slide 65
    if(validateID(strTargetID)) { // if valid ID
        int targetID = stoi(strTargetID); // convert name to int
        StudentNode *target = searchIDHelper(this->root, targetID); // check if targetID exists in tree

        if(target == nullptr) { // if targetID does not exist
            os << "unsuccessful" << endl;
        }
        else { // if targetID exists
            this->root = removeHelper(this->root, targetID);
            os << "successful" << endl;
        }
    }
    else { // invalid ID
        os << "unsuccessful" << endl;
    }
}

AVLTree::StudentNode *AVLTree::removeHelper(AVLTree::StudentNode *node, int targetID) {
    if(targetID < node->gatorID) { // if targetID is less than current gatorID, traverse left subtree
        node->left = removeHelper(node->left, targetID);
    }
    else if(targetID > node->gatorID) { // if targetID is greater than current gatorID, traverse right subtree
        node->right = removeHelper(node->right, targetID);
    }
    else if (targetID == node->gatorID) { // if targetID is found
        if(node->left == nullptr && node->right == nullptr) { // removing with no children
            delete node;
            return nullptr; // node removed
        }
        else if(node->left == nullptr || node->right == nullptr) { // removing with one child
            StudentNode *temp;
            if(node->left == nullptr) { // node has right child
                temp = node->right;
                delete node;
                return temp; // node is replaced by right child
            }
            else if(node->right == nullptr) { // node has left child
                temp = node->left;
                delete node;
                return temp; // node is replaced by left child
            }
        }
        else if(node->left != nullptr && node->right != nullptr){ // removing with two children
            StudentNode *inorderSuccessor = getInorderSuccessor(node); // find inorder successor
            node->name = inorderSuccessor->name; // replace name and gatorID with inorder successor data
            node->gatorID = inorderSuccessor->gatorID;
            node->right = removeHelper(node->right, inorderSuccessor->gatorID); // delete inorder successor
        }
    }
    return node;
}

AVLTree::StudentNode *AVLTree::getInorderSuccessor(AVLTree::StudentNode *node) { // helper function for removeHelper
    node = node->right; // go to right child
    while (node->left != nullptr) { // go to smallest gatorID in right subtree
        node = node->left; //
    }
    return node;
}

// module 5: stepik solutions 5.1c
void AVLTree::inorder(AVLTree::StudentNode *node, vector<string> &names) { // LNR
    if(node == nullptr) { // base case
        return;
    }

    inorder(node->left,  names); // traverse left subtree
    names.push_back(node->name); // add current node name to vector
    inorder(node->right, names); // traverse right subtree
}


void AVLTree::preorder(AVLTree::StudentNode *node, vector<string> &names) { // NLR
    if(node == nullptr) { // base case
        return;
    }

    names.push_back(node->name); // add current node name to vector
    preorder(node->left, names); // traverse left subtree
    preorder(node->right, names); // traverse right subtree
}

void AVLTree::postorder(AVLTree::StudentNode *node, vector<string> &names) { // LRN
    if(node == nullptr) { // base case
        return;
    }

    postorder(node->left, names); //traverse left subtree
    postorder(node->right, names); //traverse right subtree
    names.push_back(node->name); // add current node name to vector
}

void AVLTree::printInorder(ostream& os) {
    vector<string> names;
    inorder(this->root, names); // store names in vector during inorder traversal

    if(names.empty()) { // if the tree is empty
        os << "" << endl;
    }
    else {
        for(int i = 0; i < names.size() - 1; i++) {
            os << names[i] << ", "; // print inorder traversal of names with comma separation
        }
        os << names[names.size() - 1] << endl; // final name is printed without additional comma
    }
}

void AVLTree::printPreorder(ostream& os) {
    vector<string> names;
    preorder(this->root, names); // store names in vector during preorder traversal

    if(names.empty()) { // if the tree is empty
        os << "" << endl;
    }
    else {
        for(int i = 0; i < names.size() - 1; i++) {
            os << names[i] << ", "; // print preorder traversal of names with comma separation
        }
        os << names[names.size() - 1] << endl; // final name is printed without additional comma
    }
}

void AVLTree::printPostorder(ostream& os) {
    vector<string> names;
    postorder(this->root, names); // store names in vector during postorder traversal

    if(names.empty()) { // if the tree is empty
        os << "" << endl;
    }
    else {
        for(int i = 0; i < names.size() - 1; i++) {
            os << names[i] << ", "; // print postorder traversal of names with comma separation
        }
        os << names[names.size() - 1] << endl; // final name is printed without additional comma
    }
}

void AVLTree::printLevelCount(ostream& os) {
    if(this->root == nullptr) { // if tree is empty
        os << 0 << endl;
    }
    else {
        int level = getHeight(this->root);
        os << level << endl;
    }
}

int AVLTree::removeInorderHelper(AVLTree::StudentNode *node, int &count, int n) { // return gatorID of nth node
    if(node == nullptr) { // base case
        return -1;
    }

    // LNR
    int leftSubtree = removeInorderHelper(node->left, count, n); // traverse left subtree
    if(leftSubtree != -1) {
        return leftSubtree; // if found in left subtree, return instead of traversing right subtree
    }

    if(count == n) {
        return node->gatorID; // if the nth node is reached, return gatorID of nth node
    }
    count++; // increment count

    return removeInorderHelper(node->right, count, n); // traverse right subtree
}

void AVLTree::removeInorder(int n, ostream& os) {
    int count = 0;
    int targetID = removeInorderHelper(this->root, count, n); // nth nodes gatorID

    if(targetID == -1) { // if n is not within the constraints of the vector
        os << "unsuccessful" << endl;
    }
    else {
        this->root = removeHelper(this->root, targetID); // remove the nth node with the nth gatorID
        os << "successful" << endl;
    }
}

bool AVLTree::validateID(const string& strGatorID) { // ensure gatorID follows constraints
    if(strGatorID.length() != 8) { // must be 8 digits long
        return false;
    }

    for(char c : strGatorID) { // each character must be a digit
        if(!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool AVLTree::validateName(const string& name) { // ensure name follows constraints
    for(char c : name) {
        if(!isalpha(c) && !isspace(c)) { // each char must be an upper/lower case letter or space
            return false;
        }
    }
    return true;
}

