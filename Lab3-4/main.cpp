// main.cpp
// Piotr Bonar - TEP - IST 2024

#include <iostream>
#include <string>
#include "CNumber.h"

using namespace std;

// Stałe tekstowe
static const string TEST_MSG = "Running tests for CNumber class";
static const string EXPECTED_MSG = "Expected: ";
static const string GOT_MSG = ", Got: ";
static const string COMP_TESTS_MSG = "Comparison tests:";
static const string EQUAL_MSG = "num1 == num2 (Expected: ";
static const string GT_MSG = "num1 > num2 (Expected: ";
static const string LT_MSG = "num1 < num2 (Expected: ";
static const string GTE_MSG = "num1 >= num2 (Expected: ";
static const string LTE_MSG = "num1 <= num2 (Expected: ";
static const string CONCAT_RESULT_MSG = "num1 concat num2 (Result: ";
static const string CLOSE_PAREN_MSG = "): ";

static int I_TEST_1 = 12345;
static int I_TEST_2 = -678;

void runTests() {
    cout << TEST_MSG << endl;

    // Konstruktor i toString
    CNumber num1;
    num1 = I_TEST_1;
    cout << EXPECTED_MSG << I_TEST_1 << GOT_MSG << num1.toString() << endl;

    CNumber num2;
    num2 = I_TEST_2;
    cout << EXPECTED_MSG << I_TEST_2 << GOT_MSG << num2.toString() << endl;

    // Dodawanie
    CNumber sum = num1 + num2;
    cout << EXPECTED_MSG << I_TEST_1 + I_TEST_2 << GOT_MSG << sum.toString() << endl;

    // Odejmowanie
    CNumber difference = num1 - num2;
    cout << EXPECTED_MSG << I_TEST_1 - I_TEST_2 << GOT_MSG << difference.toString() << endl;

    // Mnożenie
    CNumber product = num1 * num2;
    cout << EXPECTED_MSG << I_TEST_1 * I_TEST_2 << GOT_MSG << product.toString() << endl;

    // Dzielenie
    CNumber quotient = num1 / num2;
    cout << EXPECTED_MSG << I_TEST_1 / I_TEST_2 << GOT_MSG << quotient.toString() << endl;

    // Concat
    CNumber concat = num1 % num2;

    // Porównania
    cout << COMP_TESTS_MSG << endl;
    cout << EQUAL_MSG << (I_TEST_1 == I_TEST_2) << CLOSE_PAREN_MSG << (num1 == num2) << endl;
    cout << GT_MSG << (I_TEST_1 > I_TEST_2) << CLOSE_PAREN_MSG << (num1 > num2) << endl;
    cout << LT_MSG << (I_TEST_1 < I_TEST_2) << CLOSE_PAREN_MSG << (num1 < num2) << endl;
    cout << GTE_MSG << (I_TEST_1 >= I_TEST_2) << CLOSE_PAREN_MSG << (num1 >= num2) << endl;
    cout << LTE_MSG << (I_TEST_1 <= I_TEST_2) << CLOSE_PAREN_MSG << (num1 <= num2) << endl;

    cout << CONCAT_RESULT_MSG << concat.toString() << CLOSE_PAREN_MSG << endl;
}

int main() {
    runTests();
    return 0;
}
