#pragma once
#include <string>
using namespace std;

enum class CL { CL1, CL2, CL3, CL4 };
enum class CERTI { ADV, PRO, EX };

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
