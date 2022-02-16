#include <iostream>
using namespace std;

#include "DataBase.h"

int main(void) {
	cout << "Hello" << endl;

    DataBase* database = new DataBase();
    database->add(Employee{ 2010127115, {"KBU", "MHU"}, CL::CL3, {010, 3284, 4054}, {1964,8,14}, CERTI::ADV });
    database->add(Employee{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO });
    database->add(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
    database->add(Employee{ 2011109136, {"QKAHCEX", "LTODDO"}, CL::CL4, {010, 2627, 8566}, {1964,1,30}, CERTI::PRO });
    database->add(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });

    database->search(Column::BIRTHDAY_YEAR, "1964");
    database->search(Column::PHONE_MID, "2627");
    database->search(Column::CL, "CL4");
    database->search(Column::EMPLOYEE_NUM, "11125777");
    database->search(Column::NAME, "VCUHLE HMU");


	return 0;
}