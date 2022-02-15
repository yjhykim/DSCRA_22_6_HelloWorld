#include "pch.h"
#include "../EMS/DataBase.h"
#include "mock_SearchEngine.h"

using ::testing::Test;

TEST(DataBase, Search) {
    MockSearchEngine mock_searchEngine;

    list<Employee*> employees;
    employees.emplace_back(Employee{ 2010127115, {"KBU", "MHU"}, CL::CL3, {010, 3284, 4054}, {1964,8,14}, CERTI::ADV });
    employees.emplace_back(Employee{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO });
    employees.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
    employees.emplace_back(Employee{ 2011109136, {"QKAHCEX", "LTODDO"}, CL::CL4, {010, 2627, 8566}, {1964,1,30}, CERTI::PRO });
    employees.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });

    DataBase* database = new DataBase();
    for (auto data : employees) {
        database->add(*data);
    }

    employees = database->search(Column::BIRTHDAY_YEAR, "1964");
    EXPECT_EQ(2010127115, employees.front()->employeeNum);
    EXPECT_EQ(2, employees.size());

    employees = database->search(Column::PHONE_MID, "2627");
    EXPECT_EQ(2011109136, employees.front()->employeeNum);
    EXPECT_EQ(1, employees.size());

    employees = database->search(Column::CL, "CL4");
    EXPECT_EQ(2005101762, employees.front()->employeeNum);
    EXPECT_EQ(2, employees.size());

    employees = database->search(Column::EMPLOYEE_NUM, "11125777");
    EXPECT_EQ(2011125777, employees.front()->employeeNum);
    EXPECT_EQ(1, employees.size());

    employees = database->search(Column::NAME, "VCUHLE HMU");
    EXPECT_EQ(2005101762, employees.front()->employeeNum);
    EXPECT_EQ(1, employees.size());

    list<Employee*> deleteList;
    deleteList.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
    deleteList.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });

    database->deleteTargets(deleteList);

    employees = database->search(Column::CL, "CL4");
    EXPECT_EQ(2011109136, employees.front()->employeeNum);
    EXPECT_EQ(1, employees.size());
}