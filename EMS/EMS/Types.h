#pragma once
#include <map>
#include <string>
using namespace std;

enum class CL { CL1, CL2, CL3, CL4 };

enum class CERTI { ADV, PRO, EX };

enum class Column {
	EMPLOYEE_NUM,
	NAME,
	FIRST_NAME,
	LAST_NAME,
	CL,
	PHONE,
	PHONE_MID,
	PHONE_LAST,
	BIRTHDAY,
	BIRTHDAY_YEAR,
	BIRTHDAY_MONTH,
	BIRTHDAY_DAY,
	CERTI
};

static map<CL, string> CareerLevelString = {
	{CL::CL1, "CL1"},
	{CL::CL2, "CL2"},
	{CL::CL3, "CL3"},
	{CL::CL4, "CL4"},
};

static map<CERTI, string> CertiString = {
	{CERTI::ADV, "ADV"},
	{CERTI::PRO, "PRO"},
	{CERTI::EX, "EX"},
};

const int NULL_DATA = -1;
const int EMP_ID_NUM_OF_DIGITS = 1000000;

const int MAX_OUT_DATA = 5;

const int SEPARATOR_LENGTH = 0;