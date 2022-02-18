#include "Dbms.h"
#include <vector>
#include "StringUtil.h"

Dbms::Dbms(IDataBase* db) {
	_db = db;
}

void copyResultData(list<Employee*> selectedItems, list<Employee>* result) {
	int cnt = 0;

	for (auto &item : selectedItems) {
		result->emplace_back(*item);
		if (++cnt >= MAX_OUT_DATA)
			break;
	}
}

void Dbms::add(Employee data) {
	_db->add(data);
}

int Dbms::del(Column type, string data) {
	list<Employee*> selectedItems = _db->search(type, data);
	_db->deleteTargets(selectedItems);
	return selectedItems.size();
}

list<Employee> Dbms::del_p(Column type, string data) {
	list<Employee*> selectedItems = _db->search(type, data);
	list<Employee> result;

	copyResultData(selectedItems, &result);

	_db->deleteTargets(selectedItems);

	return result;
}

int Dbms::sch(Column type, string data) {
	list<Employee*> selectedItems = _db->search(type, data);

	return selectedItems.size();
}

list<Employee> Dbms::sch_p(Column type, string data) {
	list<Employee*> selectedItems = _db->search(type, data);
	list<Employee> result;

	copyResultData(selectedItems, &result);

	return result;
}

void editColumn(Employee* target, const Column type, const string data) {
	vector<string> tokenizedStr;

	switch (type) {
	case Column::EMPLOYEE_NUM:
		target->employeeNum = stoi(data);
		break;
	case Column::NAME:
		tokenizedStr = split(data, ' ');
		target->name.first = tokenizedStr.at(0);
		target->name.last = tokenizedStr.at(1);
		break;
	case Column::CL:
		if (data == "CL1")
			target->cl = CL::CL1;
		else if (data == "CL2")
			target->cl = CL::CL2;
		else if (data == "CL3")
			target->cl = CL::CL3;
		else if (data == "CL4")
			target->cl = CL::CL4;
		break;
	case Column::PHONE:
		tokenizedStr = split(data, '-');
		target->phoneNum.start = stoi(tokenizedStr.at(0));
		target->phoneNum.mid = stoi(tokenizedStr.at(1));
		target->phoneNum.last = stoi(tokenizedStr.at(2));
		break;
	case Column::BIRTHDAY:
		target->birthDay.year = stoi(data.substr(INDEX_BIRTH_YEAR_START, LENGTH_BIRTH_YEAR));
		target->birthDay.month = stoi(data.substr(INDEX_BIRTH_MONTH_START, LENGTH_BIRTH_MONTH));
		target->birthDay.day = stoi(data.substr(INDEX_BIRTH_DAY_START, LENGTH_BIRTH_DAY));
		break;
	case Column::CERTI:
		if (data == "ADV")
			target->certi = CERTI::ADV;
		else if (data == "PRO")
			target->certi = CERTI::PRO;
		else if (data == "EX")
			target->certi = CERTI::EX;
		break;
	}
}

int Dbms::mod(Column typeFrom, string dataFrom, Column typeTo, string dataTo) {
	list<Employee*> selectedItems = _db->search(typeFrom, dataFrom);

	for (auto &e : selectedItems) editColumn(e, typeTo, dataTo);

	return selectedItems.size();
}

list<Employee> Dbms::mod_p(Column typeFrom, string dataFrom, Column typeTo, string dataTo) {
	list<Employee*> selectedItems = _db->search(typeFrom, dataFrom);
	list<Employee> result;

	copyResultData(selectedItems, &result);

	for (auto &e : selectedItems) editColumn(e, typeTo, dataTo);

	return result;
}
