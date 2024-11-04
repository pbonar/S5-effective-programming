// CNumber.h
// Piotr Bonar - TEP - IST 2024

#ifndef CNUMBER_H
#define CNUMBER_H

#include <iostream>
#include <string>

using namespace std;

class CNumber {
    public:
        bool b_positive;
        int* pi_table;
        int i_len;

    public:
        CNumber();
        ~CNumber();
        void operator=(const int iValue);
        void operator=(const CNumber &pcOther);
        int operator+(const int iValue);
        CNumber operator+(CNumber &pcOther);
        int operator-(const int iValue);
        CNumber operator-(CNumber &pcOther);
        int operator*(int iValue);
        CNumber operator*(CNumber &pcOther);
        int operator/(const int iValue);
        CNumber operator/(CNumber &pcOther);

        bool operator<(CNumber &pcOther);
        bool operator>(CNumber &pcOther);
        bool operator==(CNumber &pcOther);
        bool operator>=(CNumber &pcOther);
        bool operator<=(CNumber &pcOther);

        string toString();
        int toInt();
        CNumber operator%(CNumber &cVal);

        int getILen();
        int* getPITable();
        bool getBPositive();
        int getIndex(int index);
        void setIndex(int index, int value);
        void setILen(int value);
        void setPITable(int* table);
        void setBPositive(bool positive);

    private:
        static const int NUM_SYSTEM;
};

#endif