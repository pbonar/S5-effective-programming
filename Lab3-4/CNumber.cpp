// CNumber.cpp
// Piotr Bonar - TEP - IST 2024

#include <iostream>
#include <string>
#include <sstream>
#include "CNumber.h"

using namespace std;

const int CNumber::NUM_SYSTEM = 10;

CNumber::CNumber(){
    pi_table = new int[1];
    pi_table[0] = 0;
    i_len = 1;
    b_positive = true;
}

CNumber::~CNumber() {
    delete[] pi_table;
    pi_table = nullptr;  
}

void CNumber::operator=(const CNumber &pcOther) {
    if (this != &pcOther) {
        delete[] pi_table;

        i_len = pcOther.i_len;
        pi_table = new int[i_len];
        for (int i = 0; i < i_len; i++) {
            pi_table[i] = pcOther.pi_table[i];
        }
        b_positive = pcOther.b_positive;
    }
}

void CNumber::operator=(const int iValue) {
    int* abs_value = new int;
    *abs_value = (iValue >= 0) ? iValue : -iValue;
    b_positive = (iValue >= 0);

    int* temp_value = new int;
    *temp_value = *abs_value;
    i_len = (*temp_value == 0) ? 1 : 0;

    while (*temp_value != 0) {
        i_len++;
        *temp_value /= NUM_SYSTEM;
    }

    delete[] pi_table;
    pi_table = new int[i_len];

    *temp_value = *abs_value;
    for (int index = 0; index < i_len; index++) {
        pi_table[index] = *temp_value % NUM_SYSTEM;
        *temp_value /= NUM_SYSTEM;
    }
    delete abs_value;
    delete temp_value;
}

int CNumber::operator+(const int iValue){
    CNumber* cn_temp = new CNumber;
    *cn_temp = iValue;
    int* temp = new int;
    *temp = operator+(*cn_temp).toInt();
    delete cn_temp;
    return *temp;
}

CNumber CNumber::operator+(CNumber &pcOther) {
    if (pcOther.getBPositive() == b_positive) {
        CNumber* result = new CNumber;
        int* max_len = new int;
        *max_len = max(getILen(), pcOther.getILen());
        (*result).setILen(*max_len + 1);
        (*result).setPITable(new int[(*result).getILen()]());

        int* carry = new int;
        *carry = 0;

        int* a_digit = new int;
        int* b_digit = new int;
        for (int i = 0; i < *max_len; i++) {
            *a_digit = (i < getILen()) ? getIndex(i) : 0;
            *b_digit = (i < pcOther.getILen()) ? pcOther.getIndex(i) : 0;

            int* sum = new int;
            *sum = *a_digit + *b_digit + *carry;
            (*result).setIndex(i, *sum % NUM_SYSTEM);
            *carry = *sum / NUM_SYSTEM;
        }
        delete a_digit;
        delete b_digit;

        if (carry != 0) {
            (*result).setIndex(*max_len, *carry);
            (*result).setILen(*max_len + 1);
        } else {
            (*result).setILen(*max_len);
        }
        delete carry;

        if ((*result).getIndex((*result).getILen()-1) == 0)
            (*result).setILen((*result).getILen()-1);
        (*result).setBPositive(b_positive);
        return *result;
    } else {
        CNumber* temp_1 = new CNumber;
        *temp_1 = pcOther;
        (*temp_1).setBPositive(b_positive);
        *temp_1 = *this - *temp_1;
        return *temp_1;
    }
}

int CNumber::operator-(const int iValue){
    CNumber* cn_temp = new CNumber;
    *cn_temp = iValue;
    int* temp = new int;
    *temp = operator-(*cn_temp).toInt();
    delete cn_temp;
    return *temp;
}

CNumber CNumber::operator-(CNumber &pcOther) {
    if (b_positive && pcOther.getBPositive()) {
        if (*this < pcOther) {
            CNumber* result = new CNumber;
            *result = pcOther - *this;
            (*result).setBPositive(false);
            return *result;
        }

        CNumber* result = new CNumber;
        int* max_len = new int;
        *max_len = max(getILen(), pcOther.getILen());
        (*result).setILen(*max_len);
        (*result).setPITable(new int[(*result).getILen()]());

        int* borrow = new int;
        *borrow = 0;
        int* a_digit = new int;
        int* b_digit = new int;
        for (int i = 0; i < *max_len; i++) {
            *a_digit = (i < getILen()) ? getIndex(i) : 0;
            *b_digit= (i < pcOther.getILen()) ? pcOther.getIndex(i) : 0;

            int* sub = new int;
            *sub = *a_digit - *b_digit - *borrow;

            if (*sub < 0) {
                *sub += NUM_SYSTEM;
                *borrow = 1;
            } else {
                *borrow = 0;
            }

            (*result).setIndex(i, *sub);
        }
        delete borrow;
        delete a_digit;
        delete b_digit;

        while ((*result).getILen() > 1 && (*result).getIndex((*result).getILen() - 1) == 0) {
            (*result).setILen((*result).getILen() - 1);
        }

        (*result).setBPositive(true);
        return (*result);
    }
    else if (!b_positive && !pcOther.getBPositive()) {
        CNumber* temp_1  = new CNumber;
        CNumber* temp_2 = new CNumber;
        *temp_1 = *this;
        *temp_2 = pcOther;
        (*temp_1).setBPositive(true);
        (*temp_2).setBPositive(true);
        CNumber* result = new CNumber;
        *result = *temp_1 - *temp_2;
        delete temp_1;
        delete temp_2;
        (*result).setBPositive(false);
        return (*result);
    }
    else if (!b_positive && pcOther.getBPositive()) {
        CNumber* temp_1 = new CNumber;
        *temp_1 = pcOther;
        (*temp_1).setBPositive(false);
        *temp_1 = *temp_1 + *this;
        return *temp_1;
    }
    else {
        CNumber* temp_1 = new CNumber;
        *temp_1 = pcOther;
        (*temp_1).setBPositive(true);
        *temp_1 = *temp_1 + *this;
        return *temp_1;
    }
}

CNumber CNumber::operator*(CNumber &pcOther) {
    CNumber* result = new CNumber;
    (*result).setILen(i_len + pcOther.getILen());
    (*result).setPITable(new int[(*result).getILen()]());
    (*result).setBPositive(b_positive == pcOther.getBPositive());

    for (int i = 0; i < i_len; i++) {
        int* carry = new int;
        *carry = 0;

        for (int j = 0; j < pcOther.getILen(); j++) {
            int* prod = new int;
            *prod = getIndex(i) * pcOther.getIndex(j) + (*result).getIndex(i + j) + *carry;
            (*result).setIndex(i + j, *prod % NUM_SYSTEM);
            *carry = *prod / NUM_SYSTEM;
            delete prod;
        }

        if (*carry != 0) {
            (*result).setIndex(i + pcOther.getILen(), *carry);
        }
        delete carry;
    }

    while ((*result).getILen() > 1 && (*result).getIndex((*result).getILen() - 1) == 0) {
        (*result).setILen((*result).getILen() - 1);
    }

    return (*result);
}

CNumber CNumber::operator/(CNumber &pcOther) {
    if (pcOther.toInt() == 0) {
        return CNumber();
    }    
    CNumber* devider = new CNumber;
    CNumber* quotient = new CNumber;
    CNumber* remainder = new CNumber;
    *devider = pcOther;
    *remainder = 0;
    *quotient = 0;
    (*devider).setBPositive(true);

    if (*this < pcOther) {
        (*quotient).setILen(1);
        (*quotient).setIndex(0, 0);
        delete devider;
        delete remainder;
        return *quotient;
    }

    for (int i = i_len - 1; i >= 0; i--) { 
        *remainder = *remainder * NUM_SYSTEM + getIndex(i);

        CNumber* count = new CNumber;
        *count = 0;

        while (*remainder - (*devider * count->operator+(1)) >= 0) {
            *count = *count + 1;
        }

        *remainder = (*remainder) - (*devider * (count->toInt()));
        *quotient = *quotient * NUM_SYSTEM + count->toInt();
    }


    (*quotient).setBPositive(b_positive == pcOther.getBPositive()); 
    delete remainder;
    delete devider;

    (*quotient).setILen(i_len - pcOther.getILen() + ((pcOther.getILen() == 1) ? 0 : 1));
    while ((*quotient).getILen() > 1 && (*quotient).getIndex((*quotient).getILen() - 1) == 0) {
        (*quotient).setILen((*quotient).getILen() - 1);
    }
    return *quotient;
}

bool CNumber::operator==(CNumber &pcOther) {
    if (b_positive != pcOther.getBPositive()) {
        return false;
    }

    if (i_len != pcOther.getILen()) {
        return false;
    }

    for (int i = 0; i < i_len; i++) {
        if (getIndex(i) != pcOther.getIndex(i)) {
            return false;
        }
    }

    return true;
}

bool CNumber::operator<=(CNumber &pcOther) {
    return *this < pcOther || *this == pcOther;
}

bool CNumber::operator>=(CNumber &pcOther) {
    return *this > pcOther || *this == pcOther;
}

bool CNumber::operator>(CNumber &pcOther) {
    return !(*this <= pcOther);
}

bool CNumber::operator<(CNumber &pcOther){
    if (i_len < pcOther.getILen()) {
        return true;
    }
    if (i_len > pcOther.getILen()) {
        return false;
    }
    for (int i = i_len - 1; i >= 0; i--) {
        if (getIndex(i) < pcOther.getIndex(i)) {
            return true;
        }
        if (getIndex(i) > pcOther.getIndex(i)) {
            return false;
        }
    }
    return false;
}

int CNumber::operator*(const int iValue){
    CNumber cn_temp;
    cn_temp = iValue;
    int temp = operator*(cn_temp).toInt();
    return temp;
}

int CNumber::operator/(const int iValue){
    CNumber cn_temp;
    cn_temp = iValue;
    int temp = operator/(cn_temp).toInt();
    return temp;}

string CNumber::toString(){
    ostringstream oss;
    if (!b_positive) oss << "-";
    for (int i = i_len - 1; i >= 0; i--)
        oss << pi_table[i];
    return oss.str();
}

int CNumber::getILen(){
    return i_len;
}

int* CNumber::getPITable(){
    return pi_table;
}

bool CNumber::getBPositive(){
    return b_positive;
}

int CNumber::getIndex(int index){
    return pi_table[index];
}

void CNumber::setIndex(int index, int value){
    pi_table[index] = value;
}

void CNumber::setILen(int value){
    i_len = value;
}

void CNumber::setPITable(int* table){
    pi_table = table;
}

void CNumber::setBPositive(bool positive){
    b_positive = positive;
}

int CNumber::toInt(){
    int* value = new int;
    *value = 0;
    int* power = new int;
    *power = 1;

    for (int i = 0; i < i_len; i++) {
        *value += pi_table[i] * *power;
        *power *= NUM_SYSTEM;
    }
    delete power;
    *value = b_positive ? *value : -*value; 
    return *value;
}

CNumber CNumber::operator%(CNumber &cVal){
    int* result_len = new int;
    *result_len = cVal.getILen() + i_len;

    int* i = new int;
    *i = 0; 
    int* tab = new int[*result_len];
    while (*i < cVal.getILen()) {
        tab[*i] = cVal.getIndex(*i);
        *i = *i + 1;
    }
    int* j = new int;
    *j = 0;
    while (*j < i_len){
        tab[*i+*j] = pi_table[*j];;
        *j = *j + 1;
    }
    delete i;
    delete j;

    CNumber* result = new CNumber;
    result->setILen(*result_len);
    result->setBPositive(cVal.getBPositive() == b_positive);
    result->setPITable(tab);
    return *result;
};
