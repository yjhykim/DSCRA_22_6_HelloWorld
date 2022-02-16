#include "pch.h"
#include "../EMS/DataBase.h"
#include "mock_SearchEngine.h"

using ::testing::Test;

class FixtureDataBase : public ::testing::Test {
protected:
    void SetUp() override {
        testData.emplace_back(Employee{ 2015123099, {"VXIHXOTH", "JHOP"}, CL::CL3, {010, 3112, 2609}, {1977,12,11}, CERTI::ADV });
        testData.emplace_back(Employee{ 2017112609, {"FB", "NTAWR"}, CL::CL4, {010, 5645, 6122}, {1986,12,3}, CERTI::PRO });
        testData.emplace_back(Employee{ 2018115040, {"TTETHU", "HBO"}, CL::CL3, {010, 4581, 2050}, {2008,07,18}, CERTI::ADV });
        testData.emplace_back(Employee{ 1988114052, {"NQ", "LVARW"}, CL::CL4, {010, 4528, 3059}, {1991,10,21}, CERTI::PRO });
        testData.emplace_back(Employee{ 2019129568, {"SRERLALH", "HMEF"}, CL::CL2, {010, 3091, 9521}, {1964,9,10}, CERTI::PRO });
        testData.emplace_back(Employee{ 2017111236, {"VSID", "TVO"}, CL::CL1, {010, 3669, 1077}, {2012,7,18}, CERTI::PRO });
        testData.emplace_back(Employee{ 2018117906, {"TWU", "QSOLT"}, CL::CL4, {010, 6672, 7186}, {2003,4,13}, CERTI::PRO });
        testData.emplace_back(Employee{ 2008123556, {"WN", "XV"}, CL::CL1, {010, 7986, 5047}, {2010,6,14}, CERTI::PRO });
        testData.emplace_back(Employee{ 2002117175, {"SBILHUT", "LDEXRI"}, CL::CL4, {010, 2814, 1699}, {1995,7,4}, CERTI::ADV });
        testData.emplace_back(Employee{ 2003113260, {"HH", "LTUPF"}, CL::CL2, {010, 5798, 5383}, {1979,10,18}, CERTI::PRO });
        testData.emplace_back(Employee{ 2014130827, {"RPO", "JK"}, CL::CL4, {010, 3231, 1698}, {2009,2,1}, CERTI::ADV });
        testData.emplace_back(Employee{ 2001122329, {"DN", "WD"}, CL::CL4, {010, 7174, 5680}, {2007,11,17}, CERTI::PRO });
        testData.emplace_back(Employee{ 2008108827, {"RTAH", "VNUP"}, CL::CL4, {010, 9031, 2726}, {1978,4,17}, CERTI::ADV });
        testData.emplace_back(Employee{ 1985125741, {"FBAH", "RTIJ"}, CL::CL1, {010, 8900, 1478}, {1978,2,28}, CERTI::ADV });
        testData.emplace_back(Employee{ 2008117441, {"BMU", "MPOSXU"}, CL::CL3, {010, 2703, 3153}, {2001,2,15}, CERTI::ADV });
        testData.emplace_back(Employee{ 2010127115, {"KBU", "MHU"}, CL::CL3, {010, 3284, 4054}, {1966,8,14}, CERTI::ADV });
        testData.emplace_back(Employee{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO });
        testData.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
        testData.emplace_back(Employee{ 2011109136, {"QKAHCEX", "LTODDO"}, CL::CL4, {010, 2627, 8566}, {1964,1,30}, CERTI::PRO });
        testData.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });
    }

    void TearDown() override {}

    void addData() {
        for (auto data : testData) {
            database.add(data);
        }
    }

public:
    vector<Employee> testData;
    DataBase database;
};

TEST_F(FixtureDataBase, SearchEmployeeNum) {
    addData();

    auto employees = database.search(Column::EMPLOYEE_NUM, "17111236");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(2017111236, employees.front()->employeeNum);

    employees = database.search(Column::EMPLOYEE_NUM, "88114052");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(1988114052, employees.front()->employeeNum);

    employees = database.search(Column::EMPLOYEE_NUM, "58114052");
    EXPECT_EQ(0, employees.size());
}

TEST_F(FixtureDataBase, SearchName) {
    addData();

    auto employees = database.search(Column::NAME, "BMU MPOSXU");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(2008117441, employees.front()->employeeNum);

    employees = database.search(Column::FIRST_NAME, "RPO");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(2014130827, employees.front()->employeeNum);

    employees = database.search(Column::LAST_NAME, "JJIVL");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(2012117017, employees.front()->employeeNum);
}

TEST_F(FixtureDataBase, SearchPhoneNum) {
    addData();

    auto employees = database.search(Column::PHONE_MID, "9031");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(2008108827, employees.front()->employeeNum);

    employees = database.search(Column::PHONE, "010-3988-9289");
    ASSERT_EQ(1, employees.size());
    EXPECT_EQ(2005101762, employees.front()->employeeNum);
}

TEST_F(FixtureDataBase, SearchCerti) {
    addData();

    auto employees = database.search(Column::CERTI, "PRO");
    ASSERT_EQ(12, employees.size());
    EXPECT_EQ(1988114052, employees.front()->employeeNum);

    employees.pop_front();
    EXPECT_EQ(2001122329, employees.front()->employeeNum);
}

TEST_F(FixtureDataBase, Delete) {
    addData();

    list<Employee*> deleteEmployees;
    deleteEmployees.emplace_back(&testData.at(2));
    deleteEmployees.emplace_back(&testData.at(7));

    auto result = database.deleteTargets(deleteEmployees);
    EXPECT_EQ(true, result);

    auto employees = database.search(Column::BIRTHDAY, "20080718");
    EXPECT_EQ(0, employees.size());
    employees = database.search(Column::EMPLOYEE_NUM, "18115040");
    EXPECT_EQ(0, employees.size());
    employees = database.search(Column::EMPLOYEE_NUM, "08123556");
    EXPECT_EQ(0, employees.size());
    employees = database.search(Column::CERTI, "PRO");
    EXPECT_EQ(11, employees.size());
}