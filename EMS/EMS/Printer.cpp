#pragma once
#include "Printer.h"
#include <map>
#include <iostream>
#include <iomanip>

void Printer::print(list<Employee>& data, string& cmd) const {
    if (data.size() == 0) {
        output_ << cmd + ",NONE" << endl;
        return;
    }

    for (const auto& employee : data) {
        output_ << cmd + ",";
        output_ << std::to_string(employee.employeeNum).substr(2, 10) + ",";
        output_ << employee.name.first + " " + employee.name.last + ",";
        output_ << CareerLevelString[employee.cl] + ",";
        output_ << std::setw(3) << std::setfill('0') << employee.phoneNum.start << "-";
        output_ << std::setw(4) << std::setfill('0') << employee.phoneNum.mid << "-";
        output_ << std::setw(4) << std::setfill('0') << employee.phoneNum.last << ",";
        output_ << std::setw(4) << std::setfill('0') << employee.birthDay.year;
        output_ << std::setw(2) << std::setfill('0') << employee.birthDay.month;
        output_ << std::setw(2) << std::setfill('0') << employee.birthDay.day << ",";
        output_ << CertiString[employee.certi];
        output_ << endl;
    }
}

void Printer::print(int data, string& cmd) const {
    output_ << cmd + ",";
    if (data == 0) output_ << "NONE";
    else output_ << data;
    output_ << endl;
}