// main.cpp
// Piotr Bonar - TEP - IST 2024

#include <iostream>
#include "CTable.h"
using namespace std;

const int FILL_VALUE = 34;
const char SPACER = ' ';

const string COUT_ARRAY_START = "Zawartość tablicy: ";
const string COUT_ARRAY_WRONG_SIZE = "Nieprawidłowy rozmiar tablicy";

const string COUT_ZAD1_INTRO = "\nZadanie 1. - Testowanie tworzenia listy\nWybierz dlugosc listy: ";
const string COUT_ZAD2_INTRO = "\nZadanie 2. - Testowanie alokacji dwuwymiarowej tablicy.\nWybierz dlugosc X: ";
const string COUT_ZAD3_INTRO = "\nZadanie 3. - Testowanie delokacji dwuwymiarowej tablicy\n";
const string COUT_ZAD4_INTRO = "\nZadanie 4. - Testowanie klasy CTable\n TEST: Konstruktor\n";

const string COUT_ZAD2_INFO_COMPLETE = "Powiodło się, tablica została alokowana.\nZawartość tablicy 2D: \n";
const string COUT_ZAD3_INFO_COMPLETE = "Tablica została zwolniona.\n";
const string COUT_ZAD3_INFO_AGAIN = "Nie powiodło się, nie udało się alokować tablicy. ";
const string COUT_ZAD4_INFO_AGAIN = "Niepoprawny wybor. ";

const string COUT_ZAD2_QUES_SIZE_Y = "Wybierz dlugosc Y: ";
const string COUT_ZAD4_QUES_CONSTR = "Wybierz czy chcesz wybrac konstruktor domyslny (1) czy parametrowy (2): ";
const string COUT_ZAD4_QUES_NAME = "Wybierz nazwe tablicy: ";
const string COUT_ZAD4_QUES_SIZE = "Podaj dlugosc tablicy: ";

const string COUT_ZAD4_TEST_COUT_ARR = "\nTEST: Wyswietlanie tablicy: \n";
const string COUT_ZAD4_TEST_SET_NAME = "\nTEST: Zmiana nazwy \nPodaj nową nazwę: ";
const string COUT_ZAD4_TEST_CLONE = "\nTEST: Klonowanie\n";
const string COUT_ZAD4_TEST_SET_SIZE = "\nTEST: Nowy rozmiar\nWprowadź nowy rozmiar: ";
const string COUT_ZAD4_TEST_DESTRUCT = "\nTEST: Destruktor\nCzy dalej istnieje tempCtable: ";


void v_alloc_table_fill_34(int iSize) {
    if (iSize <= 0) {
        cout << COUT_ARRAY_WRONG_SIZE << endl;
        return;
    }
    int* pi_table = new int[iSize];

    for (int i = 0; i < iSize; ++i) {
        pi_table[i] = FILL_VALUE;
    }

    cout << COUT_ARRAY_START;
    for (int i = 0; i < iSize; ++i) {
        cout << pi_table[i] << SPACER;
    }
    cout << endl;

    delete[] pi_table;
}

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0) {
        return false;
    }

    *piTable = new int*[iSizeX];
    if (*piTable == nullptr) {
        return false;
    }

    for (int i = 0; i < iSizeX; ++i) {
        (*piTable)[i] = new int[iSizeY];
        if ((*piTable)[i] == nullptr) {
            for (int j = 0; j < i; ++j) {
                delete[] (*piTable)[j];
            }
            delete[] *piTable;
            return false;
        }
    }

    return true;
}

void v_dealloc_table_2_dim(int*** piTable, int iSizeX) {
    if (piTable == nullptr || *piTable == nullptr) {
        return;
    }
    for (int i = 0; i < iSizeX; ++i) {
        delete[] (*piTable)[i];
    }
    delete[] *piTable;
    *piTable = nullptr;
}

// ======================================================================== TESTING ====================================================================================

void test_zad1() {
    cout << COUT_ZAD1_INTRO;
    int* tempSize = new int;
    cin >> *tempSize;
    v_alloc_table_fill_34(*tempSize);
    delete tempSize;
}

void test_zad23(){
    int* tempSizeX = new int;
    int* tempSizeY = new int;
    cout << COUT_ZAD2_INTRO;
    cin >> *tempSizeX;
    cout << COUT_ZAD2_QUES_SIZE_Y;
    cin >> *tempSizeY;
    int** tempTable = nullptr;
    if (b_alloc_table_2_dim(&tempTable, *tempSizeX, *tempSizeY)) {
        cout << COUT_ZAD2_INFO_COMPLETE;
        for (int i = 0; i < *tempSizeX; ++i) {
            for (int j = 0; j < *tempSizeY; ++j) {
                cout << tempTable[i][j] << SPACER;
            }
            cout << endl;
        }

        cout << COUT_ZAD3_INTRO;
        v_dealloc_table_2_dim(&tempTable, *tempSizeX);
        cout << COUT_ZAD3_INFO_COMPLETE;
    } else {
        cout << COUT_ZAD3_INFO_AGAIN;
    }
    delete tempSizeX; 
    delete tempSizeY;
    delete tempTable;
}

void test_zad4(){
    CTable* tempCtable;
    int* tempPick = new int(0);
    
    // Test: Konstruktory
    cout << COUT_ZAD4_INTRO;
    do {
        cout << COUT_ZAD4_QUES_CONSTR;
        cin >> *tempPick;
        if (*tempPick == 1) 
            tempCtable = new CTable();
        else if (*tempPick == 2) {
            string* tempStr = new string();
            cout << COUT_ZAD4_QUES_NAME;
            cin >> *tempStr;
            int* tempSize = new int;
            do {
                cout << COUT_ZAD4_QUES_SIZE;
                cin >> *tempSize;
                if (*tempSize <= 0 ) cout << COUT_ZAD4_INFO_AGAIN;
            } while (*tempSize <= 0);
            tempCtable = new CTable(*tempStr, *tempSize);
            delete tempStr;
            delete tempSize;
        } else {
            cout << COUT_ZAD4_INFO_AGAIN;
        }
    } while (*tempPick != 1 && *tempPick != 2);

    // Test: Wyswietlanie
    cout << COUT_ZAD4_TEST_COUT_ARR;
    tempCtable->vPrintTable();

    // Test: Zmiana nazwy
    cout << COUT_ZAD4_TEST_SET_NAME;
    string* tempEntry = new string();
    cin >> *tempEntry;
    tempCtable->vSetName(*tempEntry);
    tempCtable->vPrintTable();
    delete tempEntry;

    // Test: Clone
    cout << COUT_ZAD4_TEST_CLONE;
    CTable* tempCtable_clone = tempCtable->pcClone();
    tempCtable_clone->vPrintTable();
    delete tempCtable_clone;

    // Test: Zmiana rozmiaru
    do {
        cout << COUT_ZAD4_TEST_SET_SIZE;
        cin >> *tempPick;
        if (*tempPick <= 0)
            cout << COUT_ZAD4_INFO_AGAIN;
    } while (*tempPick <= 0);
    tempCtable->bSetNewSize(*tempPick);
    tempCtable->vPrintTable();
        
    // Test: Destruktor
    cout << COUT_ZAD4_TEST_DESTRUCT;
    delete tempCtable;
    delete tempPick;
}

void test_mod() {
    CTable* tempCTable = new CTable(11);
    CTable* tempCTable_div = tempCTable->divTable();
    tempCTable->vPrintTable();
    tempCTable_div->vPrintTable();

}

int main() {
    test_mod();
    test_zad1();
    test_zad23();
    test_zad4();
    return 0;
}

