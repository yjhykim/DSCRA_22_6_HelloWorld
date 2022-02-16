#include "Dbms.h"
#include <vector>
#include <sstream>

Dbms::Dbms(IDataBase* db) {
	_db = db;
}

void Dbms::add(Employee data) {
	_db->add(data);
}

int Dbms::del(Column type, string data) {
	list<Employee*> list = _db->search(type, data);
	_db->deleteTargets(list);
	return 0;
}

list<Employee*> Dbms::del_p(Column type, string data) {
	list<Employee*> list = _db->search(type, data);
	_db->deleteTargets(list);
	return list;
}

int Dbms::sch(Column type, string data) {
	list<Employee*> list = _db->search(type, data);
	return 0;
}

list<Employee*> Dbms::sch_p(Column type, string data) {
	list<Employee*> list = _db->search(type, data);
	return list;
}

vector<string> tokenize_getline(const string& data, const char delimiter = ' ') {
	vector<string> result;
	string token;
	stringstream ss(data);

	while (getline(ss, token, delimiter)) result.push_back(token);

	return result;
}

void editColumn(Employee* target, const Column type, const string data) {
	vector<string> tokenizedStr;

	switch (type) {
	case Column::EMPLOYEE_NUM:
		target->employeeNum = stoi(data);
		break;
	case Column::NAME:
		tokenizedStr = tokenize_getline(data, ' ');
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
		tokenizedStr = tokenize_getline(data, '-');
		target->phoneNum.start = stoi(tokenizedStr.at(0));
		target->phoneNum.mid = stoi(tokenizedStr.at(1));
		target->phoneNum.last = stoi(tokenizedStr.at(2));
		break;
	case Column::BIRTHDAY:
		target->birthDay.year = stoi(data.substr(0, 4));
		target->birthDay.month = stoi(data.substr(4, 2));
		target->birthDay.day = stoi(data.substr(6, 2));
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
	list<Employee*> list = _db->search(typeFrom, dataFrom);

	for (auto e : list) editColumn(e, typeTo, dataTo);

	return 0;
}

list<Employee*> Dbms::mod_p(Column typeFrom, string dataFrom, Column typeTo, string dataTo) {
	list<Employee*> list = _db->search(typeFrom, dataFrom);

	for (auto e : list) editColumn(e, typeTo, dataTo);

	return list;
}