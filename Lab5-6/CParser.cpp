#include <iostream>
#include <sstream>
#include <string>
#include "CParser.h"

using namespace std;

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
        cout << "> ";
        getline(cin, line);
        if (line.empty()) continue;

        istringstream stream(line);
        string command;
        stream >> command;

        if (command == "enter") {
            string formula;
            getline(stream, formula);
            trim(formula);
            tree.enter(formula);
        } 
        else if (command == "vars") {
            tree.vars();
        } 
        else if (command == "print") {
            tree.printTree();
        } 
        else if (command == "comp") {
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
            cout << "Result: " << result << "\n";

        } 
        else if (command == "join") {
            string formula;
            getline(stream, formula);
            trim(formula);
            tree.join(formula);
        } 
        else if (command == "exit" || command == "quit" || command == "close") {
            cout << "Closing the terminal...\n";
            return;
        } 
        else {
            cerr << "Unknown command: " << command << "\n";
        }
    }
}
