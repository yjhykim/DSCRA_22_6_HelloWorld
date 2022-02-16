#pragma once
#include "Printer.h"
#include <map>

void ShortPrinter::print(list<Employee*> data, string cmd) const {
    // ex) DEL,3
    // ex) DEL,NONE
    string statement = cmd + ",";
    if (data.size() == 0) {
        statement += "NONE";
    }
    else {
        statement += std::to_string(data.size());
    }
    printf("%s\n", statement.c_str());
    
}

void DetailedPrinter::print(list<Employee*> data, string cmd) const {
    // ex) DEL,91351446,LIM PNQN,CL3,010-3245-2345,19940812,PRO
    string statement{ "" };
    for (const auto& employee : data) {
        statement = cmd + ",";
        statement += employee->employeeNum % 100000000 + ",";
        statement += employee->name.first + " " + employee->name.last + ",";
        statement += CareerLevelString[employee->cl] + ",";
        statement += std::to_string(employee->phoneNum.start) + "-";
        statement += std::to_string(employee->phoneNum.mid) + "-";
        statement += std::to_string(employee->phoneNum.last) + ",";
        statement += std::to_string(employee->birthDay.year);
        statement += std::to_string(employee->birthDay.month);
        statement += std::to_string(employee->birthDay.day) + ",";
        statement += CertiString[employee->certi];
        printf("%s\n", statement.c_str());
    }
}
