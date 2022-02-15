#include "Dbms.h"

Dbms::Dbms(IDataBase* db) {
	_db = db;
}

list<Employee*> Dbms::add(Employee data) {
	list<Employee*> list;
	return list;
}

list<Employee*> Dbms::del(Column type, string data) {
	list<Employee*> list;
	return list;
}

list<Employee*> Dbms::sch(Column type, string data) {
	list<Employee*> list;
	return list;
}

list<Employee*> Dbms::mod(Column typeFrom, string dataFrom, Column typeTo, string dataTo) {
	list<Employee*> list;
	return list;
}