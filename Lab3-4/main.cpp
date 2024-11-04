// main.cpp
// Piotr Bonar - TEP - IST 2024

#include <iostream>
#include <string>
#include "CNumber.h"

using namespace std;

static int I_TEST_1 = 12345;
static int I_TEST_2 = -678;

void runTests() {
    cout << "Running tests for CNumber class" << endl;

    // Konstruktor i toString
    CNumber num1;
    num1 = I_TEST_1;
    cout << "Expected: " << I_TEST_1 << ", Got: " << num1.toString() << endl;

    CNumber num2;
    num2 = I_TEST_2;
    cout << "Expected:" << I_TEST_2 << ", Got: " << num2.toString() << endl;

    // Dodawanie
    CNumber sum = num1 + num2;
    cout << "Expected: " << I_TEST_1 + I_TEST_2 << ", Got: " << sum.toString() << endl;

    // Odejmowanie
    CNumber difference = num1 - num2;
    cout << "Expected: " << I_TEST_1 - I_TEST_2 << ", Got: " << difference.toString() << endl;

    // Mnożenie
    CNumber product = num1 * num2;
    cout << "Expected: " << I_TEST_1 * I_TEST_2 << ", Got: " << product.toString() << endl;

    // Dzielenie
    CNumber quotient = num1 / num2;
    cout << "Expected: " << I_TEST_1 / I_TEST_2 << ", Got: " << quotient.toString() << endl;

    // Concat
    CNumber concat = num1 % num2;
    // Porównania
    cout << "Comparison tests:" << endl;
    cout << "num1 == num2 (Expected: " << (I_TEST_1 == I_TEST_2) << "): " << (num1 == num2) << endl;
    cout << "num1 > num2 (Expected: " << (I_TEST_1 > I_TEST_2) << "): " << (num1 > num2) << endl;
    cout << "num1 < num2 (Expected: " << (I_TEST_1 < I_TEST_2) << "): " << (num1 < num2) << endl;
    cout << "num1 >= num2 (Expected: " << (I_TEST_1 >= I_TEST_2) << "): " << (num1 >= num2) << endl;
    cout << "num1 <= num2 (Expected: " << (I_TEST_1 <= I_TEST_2) << "): " << (num1 <= num2) << endl;

    cout << "num1 concat num2 (Result: " << concat.toString() << ") " << endl;
}

int main() {
    runTests();
    return 0;
}
