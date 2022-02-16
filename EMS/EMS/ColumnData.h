#pragma once

#include <vector>
#include <sstream>

static std::vector<string> split(string str, char Delimiter) {
    istringstream iss(str);
    string buffer;

    vector<string> result;
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);
    }
    return result;
}

static int getEmployeeNum(std::string data) {
    int id{ 0 };
    try {
        id = stoi(data);
        auto year = id / EMP_ID_NUM_OF_DIGITS;
        if (year >= 69)
            id += 1900 * EMP_ID_NUM_OF_DIGITS;
        else
            id += 2000 * EMP_ID_NUM_OF_DIGITS;
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
        if (text.size() > 1)
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
    return CL::CL1;
}

static CERTI getCERTI(std::string data) {
    for (auto certi : CertiString) {
        if (certi.second == data)
            return certi.first;
    }
    return CERTI::ADV;
}

static PhoneNum getPhoneNum(Column column, std::string data) {
    PhoneNum phoneNum = PhoneNum();
    if (column == Column::PHONE) {
        auto text = split(data, '-');
        if (text.size() > 3) {
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
    int idata = stoi(data);
    int year{ NULL_DATA };
    int month{ NULL_DATA };
    int day{ NULL_DATA };

    if (column == Column::BIRTHDAY) {
        int MMdd = idata % 10000;
        year = idata / 1000;
        month = MMdd / 100;
        day = MMdd % 100;
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

    return birthday;
}
