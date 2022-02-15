#include "pch.h"
#include "../EMS/Dbms.h"
#include "mock_DataBase.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Test;

TEST(Editor, sch_positive) {
    MockDataBase mockDb;

    list<Employee*> list;
    Employee employee;
    employee.name.last = "KIM";
    employee.name.first = "YONGJUN";
    employee.employeeNum = 13059831;
    list.push_back(&employee);

    Dbms editor(&mockDb);
    list = editor.sch(Column::EMPLOYEE_NUM, "1234");

    EXPECT_EQ(list.front()->employeeNum, 1234);
    EXPECT_EQ(list.size(), 1);

}
