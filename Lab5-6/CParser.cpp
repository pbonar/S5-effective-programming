#include <iostream>
#include <sstream>
#include <string>
#include "CParser.h"

using namespace std;

const string CMD_ENTER = "enter";
const string CMD_VARS = "vars";
const string CMD_PRINT = "print";
const string CMD_COMP = "comp";
const string CMD_JOIN = "join";
const string CMD_EXIT = "exit";
const string CMD_QUIT = "quit";
const string CMD_CLOSE = "close";

const string MSG_CLOSING = "Closing the terminal...\n";
const string MSG_UNKNOWN_CMD = "Unknown command: ";
const string MSG_RESULT = "Result: ";
const string MSG_FORMULA_TOO_LONG = "Formula too long. Resulting tree: ";
const string MSG_FAILED_JOIN = "Failed to join trees.\n";
const string MSG_NO_VARS = "No variables\n";
const string MSG_NO_LEAF = "No leaf node found";
const string MSG_FAILED_TO_FIND_PARENTS = "Cant find the leafs parrent\n";
const string MSG_FIRST_TREE_EMPTY = "First tree is empty, no leafes to connect.\n";
const string MSG_SECOND_TREE_EMPTY = "Second tree is empty, no leafes to join.\n";

const string PROMPT = "> ";

void trim(string &s) {
    size_t start = s.find_first_not_of(" ");
    size_t end = s.find_last_not_of(" ");
    if (start != string::npos && end != string::npos) {
        s = s.substr(start, end - start + 1);
    } else {
        s.clear();
    }
}

void CParser::processCommands() {
    string line;
    while (true) {
        cout << PROMPT;
        getline(cin, line);
        if (line.empty()) continue;

        istringstream stream(line);
        string command;
        stream >> command;

        if (command == CMD_ENTER) {
            string formula;
            getline(stream, formula);
            trim(formula);
            tree.enter(formula);
        } 
        else if (command == CMD_VARS) {
            tree.vars();
        } 
        else if (command == CMD_PRINT) {
            tree.printTree();
        } 
        else if (command == CMD_COMP) {
            string values;
            getline(stream, values);
            trim(values);

            vector<double> nums;
            istringstream valStream(values);
            string num;
            while (valStream >> num) {
                nums.push_back(stod(num));
            }
            double result = tree.compute(nums);
            cout << MSG_RESULT << result << "\n";
        } 
        else if (command == CMD_JOIN) {
            string formula;
            getline(stream, formula);
            trim(formula);
            tree.join(formula);
        } 
        else if (command == CMD_EXIT || command == CMD_QUIT || command == CMD_CLOSE) {
            cout << MSG_CLOSING;
            return;
        } 
        else {
            cerr << MSG_UNKNOWN_CMD << command << endl;
        }
    }
}
