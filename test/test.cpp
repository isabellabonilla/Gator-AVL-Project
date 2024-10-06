// Author: Isabella Bonilla
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include "AVLTree.h"
using namespace std;

TEST_CASE("Test 1: Incorrect Commands", "[flag]") {
    AVLTree tree;

    ostringstream output; // link from FAQ Q.14
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // 1. invalid name (non-alphabetic characters) & invalid id (too long)
    tree.insert("L$$ah", "12345673820374738", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str(""); // clear output

    // 2. invalid id (name, non-numeric)
    tree.remove("Izzy", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    // 3. invalid id (too short)
    tree.searchID("12337", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    // 4. invalid name (non-alphabetic characters) & invalid id (non-numeric characters)
    tree.insert("123Iz", "X888888Z", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    // 5. invalid name (non-alphabetic characters) & invalid id (too short)
    tree.insert("m1guel cursino", "613", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    // valid name & valid id (ONLY VALID NODE)
    tree.insert("Izzy B", "77134133", output);
    REQUIRE(output.str() == "successful\n");
    output.str("");

    // print inorder traversal (only has the one valid node)
    tree.printPreorder(output);
    REQUIRE(output.str() == "Izzy B\n");

    cout.rdbuf(p_cout_streambuf);
}

TEST_CASE("Test 2: Three Edge Cases", "[flag]") {
    AVLTree tree;

    ostringstream output;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // 1. remove node that does not exist (empty tree)
    tree.remove("13475671", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    // insert node into tree
    tree.insert("Leah", "13475673", output);
    REQUIRE(output.str() == "successful\n");
    output.str(""); // clear output

    // insert node into tree
    tree.insert("Brandon", "33567523", output);
    REQUIRE(output.str() == "successful\n");
    output.str("");

    // 2. inserting a duplicate node
    tree.insert("Lily Ferner", "33567523", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    tree.insert("Lara F", "76247193", output);
    REQUIRE(output.str() == "successful\n");
    output.str(""); // clear output

    // 3. search for node that does not exist
    tree.searchName("AJ", output);
    REQUIRE(output.str() == "unsuccessful\n");
    output.str("");

    // print preorder traversal (only has first two insertions) HELP
    tree.printPreorder(output);
    REQUIRE(output.str() == "Brandon, Leah, Lara F\n");

    cout.rdbuf(p_cout_streambuf);
}

TEST_CASE("Test 3: All Four Rotations", "[flag]") {
    ostringstream output;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // 1. LL case
    SECTION("LL case") {
        AVLTree treeLL;
        treeLL.insert("Riana", "33333333", output);
        treeLL.insert("Stone", "22222222", output);
        treeLL.insert("Zeke", "11111111", output); // causes LL rotation
        output.str(""); // clear output after insertions
        treeLL.printPreorder(output);
        REQUIRE(output.str() == "Stone, Zeke, Riana\n"); // check preorder traversal to verify balanced tree structure
    }

    // 2. RR case
    SECTION("RR case") {
        AVLTree treeRR;
        treeRR.insert("Riana", "11111111", output);
        treeRR.insert("Stone", "22222222", output);
        treeRR.insert("Zeke", "33333333", output); // causes RR rotation
        output.str("");
        treeRR.printPreorder(output);
        REQUIRE(output.str() == "Stone, Riana, Zeke\n");
    }

    // 3. LR case
    SECTION("LR case") {
        AVLTree treeLR;
        treeLR.insert("Riana", "33333333", output);
        treeLR.insert("Stone", "11111111", output);
        treeLR.insert("Zeke", "22222222", output); // causes LR rotation
        output.str("");
        treeLR.printPreorder(output);
        REQUIRE(output.str() == "Zeke, Stone, Riana\n");
    }

    // 4. RL case
    SECTION("RL case") {
        AVLTree treeRL;
        treeRL.insert("Riana", "11111111", output);
        treeRL.insert("Stone", "33333333", output);
        treeRL.insert("Zeke", "22222222", output); // causes RL rotation
        output.str("");
        treeRL.printPreorder(output);
        REQUIRE(output.str() == "Zeke, Riana, Stone\n");
    }

    cout.rdbuf(p_cout_streambuf);
}

TEST_CASE("Test 4: All Three Deletion Cases", "[flag]") {
    ostringstream output;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    AVLTree tree; // initialize tree
    tree.insert("Dalton", "11111111", output); // no children
    tree.insert("Brandon", "22222222", output); // two children (Dalton, Mateo)
    tree.insert("Mateo", "33333333", output); // no children
    tree.insert("Zachary", "44444444", output); // two children (Brandon, Bri)
    tree.insert("Alise", "55555555", output); // no child
    tree.insert("Bri", "66666666", output); // two children (Alise, Keegan)
    tree.insert("Keegan", "77777777", output); // no children
    output.str("");

    // 1. no children case
    tree.remove("55555555", output); // delete Alise from tree, Bri now has one child
    output.str(""); // clear output
    tree.printInorder(output);
    REQUIRE(output.str() == "Dalton, Brandon, Mateo, Zachary, Bri, Keegan\n");
    output.str("");

    // 2. one child case
    tree.remove("66666666", output); // delete Bri from tree
    output.str("");
    tree.printInorder(output);
    REQUIRE(output.str() == "Dalton, Brandon, Mateo, Zachary, Keegan\n");
    output.str("");

    // 3. two children case
    tree.remove("22222222", output); // delete Brandon from tree
    output.str("");
    tree.printInorder(output);
    REQUIRE(output.str() == "Dalton, Mateo, Zachary, Keegan\n");
    output.str("");

    cout.rdbuf(p_cout_streambuf);
}

TEST_CASE("Test 5: Large Insertion", "[flag]") {
    AVLTree tree;
    vector<int> gatorIDs;
    vector<string> names;

    ostringstream output;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // insert 100 nodes with random gatorIDs and the same name
    for(int i = 0; i < 100; i++) {
        int gatorID = rand() % 90000000 + 10000000; // 8 digit gatorID
        tree.insert("Name", to_string(gatorID), output); // insertion
        gatorIDs.push_back(gatorID); // add id to vector
        names.push_back("Name"); // add name to vector
        output.str(""); // clear output
    }

    REQUIRE(gatorIDs.size() == 100); // check that 100 nodes were inserted
    REQUIRE(names.size() == 100);

    int removed = 0;
    while(removed < 10) { // delete 10 random nodes from the 100 that were inserted
        int index = rand() % gatorIDs.size(); // random index to select gatorID
        int gatorIDRemove = gatorIDs[index];

        tree.remove(to_string(gatorIDRemove), output); // remove random node

        if(output.str() == "successful\n") { //
            gatorIDs.erase(gatorIDs.begin() + index); // remove gatorID from vector
            names.erase(names.begin() + index); // remove name from vector
            removed++;
        }

        output.str("");
    }

    REQUIRE(gatorIDs.size() == 90); // check that 10 nodes were removed
    REQUIRE(names.size() == 90);

    string expectedOutput;
    for(int i = 0; i < names.size(); i++) { // create expected output string comma-separated with names from vector
        expectedOutput += names[i];

        if(i < names.size() - 1) {
            expectedOutput += ", ";
        }
    }

    expectedOutput += "\n";

    tree.printInorder(); // actual output
    REQUIRE(output.str() == expectedOutput); // compare actual output with expected output

    cout.rdbuf(p_cout_streambuf);
}


