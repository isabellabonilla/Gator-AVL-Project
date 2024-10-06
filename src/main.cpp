// Author: Isabella Bonilla
#include <iostream>
#include <sstream>
#include <set>
#include "AVLTree.h"
using namespace std;

int main(){
    string strCommands;
    getline(cin, strCommands); // read total number of commands from input

    int totalCommands;
    try {
        totalCommands = stoi(strCommands);
    }
    catch (invalid_argument&){ // if number of commands is not first line of input
        cout << "unsuccessful" << endl;
        return 0;
    }

    AVLTree tree;

    for(int i = 0; i < totalCommands; i++) { // run program based on number of commands
        string line;
        getline(cin, line); // gets entire line of input

        stringstream in(line);

        string command;
        in >> command;

        // validate commands
        if(command == "insert") {
            string name;
            string strGatorID;

            getline(in, name, '"');
            getline(in, name, '"'); // gets name within double quotes
            in >> strGatorID;

            tree.insert(name, strGatorID); // insert NAME ID
        }
        else if(command == "search") {
            string input;
            getline(in, input, '"'); // read input up to first double quote (rest of the input if it's a gatorID)
            getline(in, input, '"'); // read input inside of quotes (name)

            if (isdigit(input[1])){ // checks if the input is a gatorID after the whitespace
                string strGatorID = input.substr(1); // remove whitespace, only store gatorID
                tree.searchID(strGatorID); // search ID
            }
            else { // if input doesn't start with a digit, then the input is a name
                tree.searchName(input); // search NAME
            }
        }
        else if(command == "remove") {
            string strGatorID;
            in >> strGatorID;

            tree.remove(strGatorID); // remove ID
        }
        else if(command == "printInorder") {
            tree.printInorder();

        }
        else if(command == "printPreorder") {
            tree.printPreorder();

        }
        else if(command == "printPostorder") {
            tree.printPostorder();

        }
        else if(command == "printLevelCount") {
            tree.printLevelCount();

        }
        else if(command == "removeInorder") {
            int n;
            in >> n;
            tree.removeInorder(n); // removeInorder N
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }

	return 0;
}
