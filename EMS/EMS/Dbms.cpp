#include "Dbms.h"
#include <vector>
#include "StringUtil.h"

Dbms::Dbms(IDataBase* db) {
	db_ = db;
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
	db_->add(data);
}

int Dbms::del(Column type, string data) {
	list<Employee*> selectedItems = db_->search(type, data);
	db_->deleteTargets(selectedItems);
	return selectedItems.size();
}

list<Employee> Dbms::del_p(Column type, string data) {
	list<Employee*> selectedItems = db_->search(type, data);
	list<Employee> result;

	copyResultData(selectedItems, &result);

	db_->deleteTargets(selectedItems);

	return result;
}

int Dbms::sch(Column type, string data) {
	list<Employee*> selectedItems = db_->search(type, data);

	return selectedItems.size();
}

list<Employee> Dbms::sch_p(Column type, string data) {
	list<Employee*> selectedItems = db_->search(type, data);
	list<Employee> result;

	copyResultData(selectedItems, &result);

	return result;
}

int Dbms::mod(Column typeFrom, string dataFrom, Column typeTo, string dataTo) {
	list<Employee*> selectedItems = db_->search(typeFrom, dataFrom);

	for (auto &e : selectedItems) db_->modifyTarget(e->employeeNum, typeTo, dataTo);

	return selectedItems.size();
}

list<Employee> Dbms::mod_p(Column typeFrom, string dataFrom, Column typeTo, string dataTo) {
	list<Employee*> selectedItems = db_->search(typeFrom, dataFrom);
	list<Employee> result;

	copyResultData(selectedItems, &result);

	for (auto &e : selectedItems) db_->modifyTarget(e->employeeNum, typeTo, dataTo);

	return result;
}
