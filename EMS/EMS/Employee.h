#pragma once
#include <string>
#include "Types.h"
using namespace std;

struct Name {
	string first;
	string last;
};
struct PhoneNum {
	int start;
	int mid;
	int last;
};
struct Birthday {
	int year;
	int month;
	int day;
};

struct Employee {
	int employeeNum;
	Name name;
	CL cl;
	PhoneNum phoneNum;
	CERTI certi;
};
