#include "DataBase.h"

void DataBase::setSearchEngine(ISearchEngine* engine) {
    delete engine_;
    engine_ = static_cast<SearchEngine*>(engine);
}

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
            return engine_->search(database_, birthday);
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
        cout << "search data is not valid: " << data << std::endl;
        cout << e.what() << std::endl;
    }
    return list<Employee*>();
}

bool DataBase::add(Employee target) {
    Employee emp = target;
    database_[emp.employeeNum] = emp;
    return true;
}

bool DataBase::deleteTargets(list<Employee*> target) {
    for (auto employee : target) {
        database_.erase(employee->employeeNum);
    }
    return true;
}

bool DataBase::modifyTarget(EmployeeNum id, Column column, string data) {

    return true;
}