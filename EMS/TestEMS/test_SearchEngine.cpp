#include "pch.h"
#include "../EMS/SearchEngine.h"
#include "../Types.h"
#include <iostream>
using namespace std;
using ::testing::Return;

class FixtureSearchEngine : public ::testing::Test {
protected:
    void SetUp() override {
        db.emplace_back(Employee{ 2015123099, {"VXIHXOTH", "JHOP"}, CL::CL3, {010, 3112, 2609}, {1977,12,11}, CERTI::ADV });
        db.emplace_back(Employee{ 2017112609, {"FB", "NTAWR"}, CL::CL4, {010, 5645, 6122}, {1986,12,3}, CERTI::PRO });
        db.emplace_back(Employee{ 2018115040, {"TTETHU", "HBO"}, CL::CL3, {010, 4581, 2050}, {2008,07,18}, CERTI::ADV });
        db.emplace_back(Employee{ 1988114052, {"NQ", "LVARW"}, CL::CL4, {010, 4528, 3059}, {1991,10,21}, CERTI::PRO });
        db.emplace_back(Employee{ 2019129568, {"SRERLALH", "HMEF"}, CL::CL2, {010, 3091, 9521}, {1964,9,10}, CERTI::PRO });
        db.emplace_back(Employee{ 2017111236, {"VSID", "TVO"}, CL::CL1, {010, 3669, 1077}, {2012,7,18}, CERTI::PRO });
        db.emplace_back(Employee{ 2018117906, {"TWU", "QSOLT"}, CL::CL4, {010, 6672, 7186}, {2003,4,13}, CERTI::PRO });
        db.emplace_back(Employee{ 2008123556, {"WN", "XV"}, CL::CL1, {010, 7986, 5047}, {2010,6,14}, CERTI::PRO });
        db.emplace_back(Employee{ 2002117175, {"SBILHUT", "LDEXRI"}, CL::CL4, {010, 2814, 1699}, {1995,7,4}, CERTI::ADV });
        db.emplace_back(Employee{ 2003113260, {"HH", "LTUPF"}, CL::CL2, {010, 5798, 5383}, {1979,10,18}, CERTI::PRO });
        db.emplace_back(Employee{ 2014130827, {"RPO", "JK"}, CL::CL4, {010, 3231, 1698}, {2009,2,1}, CERTI::ADV });
        db.emplace_back(Employee{ 2001122329, {"DN", "WD"}, CL::CL4, {010, 7174, 5680}, {2007,11,17}, CERTI::PRO });
        db.emplace_back(Employee{ 2008108827, {"RTAH", "VNUP"}, CL::CL4, {010, 9031, 2726}, {1978,4,17}, CERTI::ADV });
        db.emplace_back(Employee{ 1985125741, {"FBAH", "RTIJ"}, CL::CL1, {010, 8900, 1478}, {1978,2,28}, CERTI::ADV });
        db.emplace_back(Employee{ 2008117441, {"BMU", "MPOSXU"}, CL::CL3, {010, 2703, 3153}, {2001,2,15}, CERTI::ADV });
        db.emplace_back(Employee{ 2010127115, {"KBU", "MHU"}, CL::CL3, {010, 3284, 4054}, {1966,8,14}, CERTI::ADV });
        db.emplace_back(Employee{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO });
        db.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
        db.emplace_back(Employee{ 2011109136, {"QKAHCEX", "LTODDO"}, CL::CL4, {010, 2627, 8566}, {1964,1,30}, CERTI::PRO });
        db.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });
    }

    void TearDown() override {
    }

public:
    list<Employee> db;
};

TEST_F(FixtureSearchEngine, SearchByEmployeeNum) {
    SearchEngine se;
    
    EXPECT_EQ(0, se.search(db, 1965000000).size());
    EXPECT_EQ(0, se.search(db, 2022000000).size());

    auto result = se.search(db, 2010127115);
    ASSERT_EQ(1, result.size());
    auto item = result.begin();
    EXPECT_EQ("KBU", (*item)->name.first);
}

TEST_F(FixtureSearchEngine, SearchByName) {
    SearchEngine se;

    auto result = se.search(db, Name{ "VXIHXOTH", "JHOP" });
    ASSERT_EQ(1, result.size());
    auto item = result.begin();
    EXPECT_EQ(2015123099, (*item)->employeeNum);

    result = se.search(db, Name{ "VCUHLE", "" });
    ASSERT_EQ(1, result.size());
    item = result.begin();
    EXPECT_EQ(2005101762, (*item)->employeeNum);

    result = se.search(db, Name{ "", "VNUP" });
    ASSERT_EQ(1, result.size());
    item = result.begin();
    EXPECT_EQ(2008108827, (*item)->employeeNum);
}

TEST_F(FixtureSearchEngine, SearchByCL) {
    SearchEngine se;

    auto result = se.search(db, CL::CL2);

    ASSERT_EQ(2, result.size());
    auto item = result.begin();
    EXPECT_EQ(2019129568, (*item)->employeeNum); item = next(item);
    EXPECT_EQ(2003113260, (*item)->employeeNum); item = next(item);

    result = se.search(db, CL::CL1);
    ASSERT_EQ(5, result.size());

    result = se.search(db, CL::CL3);
    ASSERT_EQ(4, result.size());

    result = se.search(db, CL::CL4);
    ASSERT_EQ(9, result.size());
}

TEST_F(FixtureSearchEngine, SearchByPhoneNum) {
    SearchEngine se;

    auto result = se.search(db, PhoneNum{ 010, 9031, 2726 });
    ASSERT_EQ(1, result.size());
    auto item = result.begin();
    EXPECT_EQ(2008108827, (*item)->employeeNum);

    result = se.search(db, PhoneNum{ -1, 7174 , -1 });
    ASSERT_EQ(1, result.size());
    item = result.begin();
    EXPECT_EQ(2001122329, (*item)->employeeNum);

    result = se.search(db, PhoneNum{ -1, -1, 8566 });
    ASSERT_EQ(1, result.size());
    item = result.begin();
    EXPECT_EQ(2011109136, (*item)->employeeNum);
}


TEST_F(FixtureSearchEngine, SearchByBirthDay) {
    SearchEngine se;

    auto result = se.search(db, Birthday{ 1978, -1, -1 });
    ASSERT_EQ(2, result.size());
    auto item = result.begin();
    EXPECT_EQ(2008108827, (*item)->employeeNum); item = next(item);
    EXPECT_EQ(1985125741, (*item)->employeeNum); item = next(item);

    result = se.search(db, Birthday{ -1, 2, -1 });
    EXPECT_EQ(3, result.size());

    result = se.search(db, Birthday{ -1, -1, 18 });
    EXPECT_EQ(3, result.size());
}


TEST_F(FixtureSearchEngine, SearchByCerti) {
    SearchEngine se;

    auto result = se.search(db, CERTI::ADV);
    EXPECT_EQ(8, result.size());
    result = se.search(db, CERTI::PRO);
    EXPECT_EQ(12, result.size());
    result = se.search(db, CERTI::EX);
    EXPECT_EQ(0, result.size());
}