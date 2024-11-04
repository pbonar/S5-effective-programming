// CTable.h
// Piotr Bonar - TEP - IST 2024

#ifndef CTABLE_H
#define CTABLE_H

#include <iostream>
#include <string>

using namespace std;

class CTable {
    private:
        string s_name;
        int* table;
        int tableLen;

    public:
        CTable();
        CTable(int tableLen);
        CTable(string sName, int iTableLen);
        CTable(const CTable *pcOther);
        ~CTable();

        void vSetName(string sName);
        bool bSetNewSize(int iTableLen);
        CTable* pcClone();
        void vPrintTable();
        CTable* divTable();
        int iGetIndex(int iIndex);
        bool bSetIndex(int iIndex, int iValue);
        int* CTable::copyTable();

    private:
        static const string DEFAULT_NAME;
        static const int DEFAULT_TABLE_LENGTH;
        static const int DEFAULT_VALUE;
        static const string COPY_SUFFIX;
        static const string DIV2_SUFFIX; 
        static const string NOT_DIV2_SUFFIX;
        static const string COUT_START_BEZP;
        static const string COUT_START_PARA;
        static const string COUT_START_COPY;
        static const string COUT_START_DEST;
        static const string COUT_END;
        static const string COUT_SPACER;
        static const string COUT_START_WYSW;
};

#endif
