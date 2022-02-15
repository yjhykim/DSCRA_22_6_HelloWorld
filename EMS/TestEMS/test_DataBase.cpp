#include "pch.h"
#include "../EMS/DataBase.h"
#include "mock_SearchEngine.h"

using ::testing::Test;

class DataBaseTest : public testing::Test {
public:
    virtual ~DataBaseTest(){}

    virtual void SetUp() override{
        database = new DataBase();

        test_employees.emplace_back(Employee{ 2010127115, {"KBU", "MHU"}, CL::CL3, {010, 3284, 4054}, {1964,8,14}, CERTI::ADV });
        test_employees.emplace_back(Employee{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO });
        test_employees.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
        test_employees.emplace_back(Employee{ 2011109136, {"QKAHCEX", "LTODDO"}, CL::CL4, {010, 2627, 8566}, {1964,1,30}, CERTI::PRO });
        test_employees.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });

    }

    virtual void TearDown() override {
        delete database;
    }

    DataBase* database;
    list<Employee*> test_employees;
};

TEST_F(DataBaseTest, Search) {
    for (auto data : test_employees) {
        database->add(*data);
    }

    auto employees = database->search(Column::BIRTHDAY_YEAR, "1964");
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

TEST_F(DataBaseTest, delete) {
    list<Employee*> deleteList;
    deleteList.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
    deleteList.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });

    database->deleteTargets(deleteList);

    auto employees = database->search(Column::CL, "CL4");
    EXPECT_EQ(2011109136, employees.front()->employeeNum);
    EXPECT_EQ(1, employees.size());
}