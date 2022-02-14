#include <string>
#include "Employee.h"

enum Column { EMPLOYEE_NUM, NAME, CL, PHONE, BIRTH_DAY, CERTI };

class Editor {
	bool ADD(Employee data);
	bool DEL(Column type, string data);
	bool SCH(Column type, string data);
	bool MOD(Column typeFrom, string dataFrom, Column typeTo, string dataTo);
};
