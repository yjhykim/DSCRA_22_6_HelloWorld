#include <string>
#include "Employee.h"

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

class Editor {
	bool ADD(Employee data);
	bool DEL(Column type, string data);
	bool SCH(Column type, string data);
	bool MOD(Column typeFrom, string dataFrom, Column typeTo, string dataTo);
};
