#pragma once

#include <list>
#include "Employee.h"

using namespace std;

class IPrinter {
	virtual void print(list<Employee*> data) const = 0;
};