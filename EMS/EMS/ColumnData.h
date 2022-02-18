#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include "StringUtil.h"

static int getEmployeeNum(std::string data) {
    int id{ 0 };
    try {
        id = stoi(data);
        auto year = id / EMP_ID_NUM_OF_DIGITS;
        if (year >= EMP_ID_YEAR_START)
            id += EMP_ID_PREFIX_1900s;
        else
            id += EMP_ID_PREFIX_2000s;
    }
    catch (const std::exception& e) {
        throw e;
    }
    return id;
}

static Name getName(Column column, std::string data) {
    Name name{};
    if (column == Column::NAME) {
        auto text = split(data, ' ');
        if (text.size() == COUNT_NAME_SPLIT)
            name = Name{ text[0], text[1] };
    }
    else if (column == Column::FIRST_NAME) {
        name = Name{ data, "" };
    }
    else if (column == Column::LAST_NAME) {
        name = Name{ "", data };
    }
    return name;
}

static CL getCL(std::string data) {
    for (auto cl : CareerLevelString) {
        if (cl.second == data)
            return cl.first;
    }
    throw invalid_argument("CL should be one of CL1,CL2,CL3,Cl4");
}

static CERTI getCERTI(std::string data) {
    for (auto certi : CertiString) {
        if (certi.second == data)
            return certi.first;
    }
    throw invalid_argument("CERTI should be one of ADV,PRO,EX");
}

static PhoneNum getPhoneNum(Column column, std::string data) {
    PhoneNum phoneNum = PhoneNum();
    if (column == Column::PHONE) {
        auto text = split(data, '-');
        if (text.size() == COUNT_PHONE_NUM_SPLIT) {
            phoneNum = PhoneNum{
                stoi(text[0]), stoi(text[1]), stoi(text[2]) };
        }
    }
    else if (column == Column::PHONE_MID) {
        phoneNum = PhoneNum{ NULL_DATA, stoi(data), NULL_DATA };
    }
    else if (column == Column::PHONE_LAST) {
        phoneNum = PhoneNum{ NULL_DATA, NULL_DATA, stoi(data) };
    }
    return phoneNum;
}

static Birthday getBirthDay(Column column, std::string data) {
    Birthday birthday = Birthday();
    try {
        int idata = stoi(data);
        int year{ NULL_DATA };
        int month{ NULL_DATA };
        int day{ NULL_DATA };

        if (column == Column::BIRTHDAY) {
            year = stoi(data.substr(INDEX_BIRTH_YEAR_START, LENGTH_BIRTH_YEAR));
            month = stoi(data.substr(INDEX_BIRTH_MONTH_START, LENGTH_BIRTH_MONTH));
            day = stoi(data.substr(INDEX_BIRTH_DAY_START, LENGTH_BIRTH_DAY));
        }
        else if (column == Column::BIRTHDAY_YEAR) {
            year = idata;
        }
        else if (column == Column::BIRTHDAY_MONTH) {
            month = idata;
        }
        else if (column == Column::BIRTHDAY_DAY) {
            day = idata;
        }
        birthday = Birthday{ year, month, day };
    }
    catch (const exception& e) {
        cout << "birthday data is not valid: " << data << std::endl;
        cout << e.what() << std::endl;
    }
    return birthday;
}
