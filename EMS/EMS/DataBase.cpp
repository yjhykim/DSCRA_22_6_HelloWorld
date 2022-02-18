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

//void editColumn(Employee* target, const Column type, const string data) {
//	vector<string> tokenizedStr;
//
//	switch (type) {
//	case Column::EMPLOYEE_NUM:
//		target->employeeNum = stoi(data);
//		break;
//	case Column::NAME:
//		tokenizedStr = split(data, ' ');
//		target->name.first = tokenizedStr.at(0);
//		target->name.last = tokenizedStr.at(1);
//		break;
//	case Column::CL:
//		if (data == "CL1")
//			target->cl = CL::CL1;
//		else if (data == "CL2")
//			target->cl = CL::CL2;
//		else if (data == "CL3")
//			target->cl = CL::CL3;
//		else if (data == "CL4")
//			target->cl = CL::CL4;
//		break;
//	case Column::PHONE:
//		tokenizedStr = split(data, '-');
//		target->phoneNum.start = stoi(tokenizedStr.at(0));
//		target->phoneNum.mid = stoi(tokenizedStr.at(1));
//		target->phoneNum.last = stoi(tokenizedStr.at(2));
//		break;
//	case Column::BIRTHDAY:
//		target->birthDay.year = stoi(data.substr(INDEX_BIRTH_YEAR_START, LENGTH_BIRTH_YEAR));
//		target->birthDay.month = stoi(data.substr(INDEX_BIRTH_MONTH_START, LENGTH_BIRTH_MONTH));
//		target->birthDay.day = stoi(data.substr(INDEX_BIRTH_DAY_START, LENGTH_BIRTH_DAY));
//		break;
//	case Column::CERTI:
//		if (data == "ADV")
//			target->certi = CERTI::ADV;
//		else if (data == "PRO")
//			target->certi = CERTI::PRO;
//		else if (data == "EX")
//			target->certi = CERTI::EX;
//		break;
//	}
//}

bool DataBase::modifyTarget(EmployeeNum id, Column column, string data) {
    if (database_.count(id) == 0) {
        return false;
    }

	switch (column) {
	case Column::EMPLOYEE_NUM:
        database_[id].employeeNum = getEmployeeNum(data);
		break;
	case Column::NAME:
        database_[id].name = getName(column, data);
		break;
	case Column::CL:
        database_[id].cl = getCL(data);
		break;
	case Column::PHONE:
        database_[id].phoneNum = getPhoneNum(column, data);
		break;
	case Column::BIRTHDAY:
        database_[id].birthDay = getBirthDay(column, data);
		break;
	case Column::CERTI:
        database_[id].certi = getCERTI(data);
		break;
	}
    return true;
}