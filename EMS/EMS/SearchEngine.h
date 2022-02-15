#pragma once
#include <list>
#include "Employee.h"

class ISearchEngine {
public:
	virtual ~ISearchEngine() {}
	virtual list<Employee*> Search(int employeeNum) const = 0;
	virtual list<Employee*> Search(Name& name) const = 0;
	virtual list<Employee*> Search(CL& cl) const = 0;
	virtual list<Employee*> Search(PhoneNum& phoneNum) const = 0;
	virtual list<Employee*> Search(CERTI& certi) const = 0;
};

class SearchEngine : public ISearchEngine {
public:
	virtual list<Employee*> Search(int employeeNum) const override;
	virtual list<Employee*> Search(Name& name) const override;
	virtual list<Employee*> Search(CL& cl) const override;
	virtual list<Employee*> Search(PhoneNum& phoneNum) const override;
	virtual list<Employee*> Search(CERTI& certi) const override;
};