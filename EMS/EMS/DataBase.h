#pragma once

#include <vector>
#include <iostream>
#include "Employee.h"
#include "Config.h"

using namespace std;

class DataBase {
public:
	DataBase() { 
		db.reserve(MAX_EMPLOYEE_NUM);
	}
	template<typename UnaryPredicate>
	vector<Employee*> search(UnaryPredicate p, const string& word);
	unsigned int deleteTargets(vector<Employee*> targets);

private:
	vector<Employee> db;
};
