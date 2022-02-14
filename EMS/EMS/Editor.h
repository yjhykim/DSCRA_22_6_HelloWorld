#include <string>
#include "Employee.h"

enum Column { EMPLOYEE_NUM, NAME, CL, PHONE, BIRTH_DAY, CERTI }

class Editor {
	bool ADD(Employee data);
	bool DEL(Column type, string data);
	bool SCH(Column type, string data);
	bool MOD(Column type1, string data1, Column type2, string data2);
};
