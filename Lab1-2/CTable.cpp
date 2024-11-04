// CTable.cpp
// Piotr Bonar - TEP - IST 2024

#include <iostream>
#include <string>
#include "CTable.h"

using namespace std;

const string CTable::DEFAULT_NAME = "default";
const int CTable::DEFAULT_TABLE_LENGTH = 10;
const int CTable::DEFAULT_VALUE = 0;

const string CTable::COPY_SUFFIX = "_COPY";
const string CTable::DIV2_SUFFIX = "_div2";
const string CTable::NOT_DIV2_SUFFIX = "_not_div2";

const string CTable::COUT_END = "'";
const string CTable::COUT_START_BEZP = "bezp: '";
const string CTable::COUT_START_PARA = "parametr: '";
const string CTable::COUT_START_COPY = "kopiuj: '";
const string CTable::COUT_START_DEST = "usuwam: '";
const string CTable::COUT_START_WYSW = "Wyswietlam tablice: ";
const string CTable::COUT_SPACER = " ";


CTable::CTable() {
    s_name = DEFAULT_NAME;
    tableLen = DEFAULT_TABLE_LENGTH;
    table = new int[tableLen];
    for (int i = 0; i < tableLen; i++) {
        table[i] = DEFAULT_VALUE;
    }
    cout << COUT_START_BEZP << s_name << COUT_END << endl;
}

CTable::CTable(int tableLen){
    s_name = DEFAULT_NAME;
    this->tableLen = tableLen;
    table = new int[tableLen];
    for (int i = 0; i < tableLen; i++) {
        table[i] = i;
    }
    cout << COUT_START_BEZP << s_name << COUT_END << endl;
}

CTable::CTable(string sName, int iTableLen) {
    s_name = sName;
    tableLen = iTableLen;
    table = new int[tableLen];
    for (int i = 0; i < tableLen; i++) {
        table[i] = DEFAULT_VALUE;
    }
    cout << COUT_START_PARA << s_name << COUT_END << endl;
}

CTable::CTable(const CTable *pcOther) {
    s_name = pcOther->s_name + COPY_SUFFIX;
    tableLen = pcOther->tableLen;
    table = copyTable();
    cout << COUT_START_COPY << s_name << COUT_END<< endl;
}

CTable::~CTable() {
    delete[] table;
    cout << COUT_START_DEST << s_name << COUT_END << endl;
}

void CTable::vSetName(string sName) {
    this->s_name = sName;
}

// bool CTable::bSetNewSize(int iTableLen) {
//     if (iTableLen <= 0) 
//         return false;
//     delete[] table;
//     tableLen = iTableLen;
//     table = new int[tableLen];
//     for (int i = 0; i < tableLen; i++) {
//         table[i] = DEFAULT_VALUE;
//     }
//     return true;
// }

bool CTable::bSetNewSize(int iTableLen) {
    if (iTableLen <= 0) 
        return false;

    int* newTable = new int[iTableLen];
    int* minSize = new int;
    if (iTableLen > tableLen){
        *minSize = tableLen;
    }
    else { 
        *minSize = iTableLen;
    }
    for (int i = 0; i < *minSize; i++) {
        newTable[i] = table[i]; 
    }

    for (int i = *minSize; i < iTableLen; i++) {
        newTable[i] = DEFAULT_VALUE;
    }

    delete[] table;
    table = newTable;
    tableLen = iTableLen;

    return true;
}

int* CTable::copyTable() {
    int* newTable = new int[tableLen];
    for (int i = 0; i < tableLen; i++) {
        newTable[i] = table[i];
    }
}

CTable* CTable::pcClone() {
    CTable* newClone = new CTable(s_name, tableLen);
    this->table = copyTable();
    return newClone;
}

void CTable::vPrintTable() {
    cout << COUT_START_WYSW << s_name << COUT_SPACER << tableLen << endl;
    for (int i = 0; i < tableLen; i++) {
        cout << table[i] << COUT_SPACER;
    }
    cout << endl;
}

CTable* CTable::divTable() {
    CTable* tempCtableDiv2 = new CTable(s_name + DIV2_SUFFIX, tableLen);
    s_name = s_name + NOT_DIV2_SUFFIX;
    int counterDiv2 = 0;
    int counterNotDiv2 = 0;
    
    for (int i = 0; i < tableLen; i++) {
        if (iGetIndex(i) % 2 == 0) {
            tempCtableDiv2->bSetIndex(counterDiv2, iGetIndex(i));
            counterDiv2++;
        } else {
            bSetIndex(counterNotDiv2, iGetIndex(i));
            counterNotDiv2++;
        }
    }
    
    // tempCtableDiv2->vPrintTable();
    // vPrintTable();

    tempCtableDiv2->bSetNewSize(counterDiv2);
    bSetNewSize(counterNotDiv2);

//    tempCtableDiv2->vPrintTable();
//     vPrintTable();

    return tempCtableDiv2;
}


int CTable::iGetIndex(int iIndex) {
    if (iIndex >= 0 && iIndex < this->tableLen) {
        return table[iIndex];
    } else {
        return -1; 
    }
}

bool CTable::bSetIndex(int iIndex, int iValue) {
    if (iIndex >= 0 && iIndex < tableLen) {
        table[iIndex] = iValue;
        return true;
    } else {
        return false;
    }
}
