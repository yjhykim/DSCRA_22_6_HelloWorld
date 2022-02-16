#pragma once
#include <map>
#include <list>
#include "Employee.h"

class ISearchEngine {
public:
	virtual ~ISearchEngine() {}
	virtual list<Employee*> search(map<int, Employee>& db, int employeeNum) const = 0;
	virtual list<Employee*> search(map<int, Employee>& db, Name& name) const = 0;
	virtual list<Employee*> search(map<int, Employee>& db, CL cl) const = 0;
	virtual list<Employee*> search(map<int, Employee>& db, PhoneNum& phoneNum) const = 0;
	virtual list<Employee*> search(map<int, Employee>& db, Birthday& birthDay) const = 0;
	virtual list<Employee*> search(map<int, Employee>& db, CERTI certi) const = 0;
};

class SearchEngine : public ISearchEngine {
public:
	virtual list<Employee*> search(map<int, Employee>& db, int employeeNum) const override;
	virtual list<Employee*> search(map<int, Employee>& db, Name& name) const override;
	virtual list<Employee*> search(map<int, Employee>& db, CL cl) const override;
	virtual list<Employee*> search(map<int, Employee>& db, PhoneNum& phoneNum) const override;
	virtual list<Employee*> search(map<int, Employee>& db, Birthday& birthDay) const override;
	virtual list<Employee*> search(map<int, Employee>& db, CERTI certi) const override;
};