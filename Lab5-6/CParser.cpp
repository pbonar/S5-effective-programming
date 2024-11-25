#include <iostream>
#include <sstream>
#include <string>
#include "CParser.h"

using namespace std;

void trim(string &s) {
    // Helper function to trim leading and trailing spaces
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
        cout << ">>> ";
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
            tree.printTree(); // Correct method name
        } 
        else if (command == "comp") {
            string values;
            getline(stream, values);
            trim(values);

            // Parse values into vector<double>
            vector<double> nums;
            istringstream valStream(values);
            string num;
            while (valStream >> num) {
                nums.push_back(stod(num)); // Convert string to double
            }

            try {
                double result = tree.compute(nums);
                cout << "Result: " << result << "\n";
            } catch (const exception &e) {
                cerr << "Error during computation: " << e.what() << "\n";
            }
        } 
        else if (command == "join") {
            string formula;
            getline(stream, formula);
            trim(formula);
            tree.join(formula);
        } 
        else if (command == "exit") {
            cout << "Exiting...\n";
            return;
        } 
        else {
            cerr << "Unknown command: " << command << "\n";
        }
    }
}
