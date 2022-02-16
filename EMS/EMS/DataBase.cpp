#include "DataBase.h"

list<Employee*> DataBase::search(Column column, string data) {
    try {
        switch (column)
        {
        case Column::EMPLOYEE_NUM:
        {
            return engine_->search(database_, getEmployeeNum(data));
        }
        case Column::NAME:
        case Column::FIRST_NAME:
        case Column::LAST_NAME:
        {
            auto name = getName(column, data);
            return engine_->search(database_, name);
        }
        case Column::CL:
        {
            auto cl = getCL(data);
            return engine_->search(database_, cl);
        }
        case Column::PHONE:
        case Column::PHONE_MID:
        case Column::PHONE_LAST:
        {
            auto phoneNum = getPhoneNum(column, data);
            return engine_->search(database_, phoneNum);
        }
        case Column::BIRTHDAY:
        case Column::BIRTHDAY_YEAR:
        case Column::BIRTHDAY_MONTH:
        case Column::BIRTHDAY_DAY:
        {
            auto birthday = getBirthDay(column, data);
            //return engine_.search(database_, birthday); // search 함수 생기면 주석 해제
        }
        case Column::CERTI:
        {
            auto certi = getCERTI(data);
            return engine_->search(database_, certi);
        }
        default:
            break;
        }
    }
    catch (const std::exception& e) {
        //
    }
    return list<Employee*>();
}

bool DataBase::add(Employee target) {
    database_.emplace_back(&target);
    return true;
}

bool DataBase::deleteTargets(list<Employee*> target) {
    for (auto employee : target) {
        auto id = employee->employeeNum;

        auto result = std::find_if(database_.begin(), database_.end(),
            [&id](Employee* e) {return e->employeeNum == id; });

        if (result != database_.end()) {
            database_.erase(result);
        }
    }
    return true;
}