
#include "pch.h"
#include "../EMS/Dbms.h"
#include "mock_DataBase.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Test;
using ::testing::Invoke;



class DbmsTest : public testing::Test {
public:
    MockDataBase mockDb;
    Dbms* dbms;
    list<Employee*> fake_db;

    Employee data0{ 1909108827, { "RTAH", "VNUP" }, CL::CL4, { 010, 9031, 2726 }, { 1978,4,17 }, CERTI::ADV };
    Employee data1{ 1910127115, {"KBU", "KIM"}, CL::CL3, {010, 3284, 4054}, {1966,8,14}, CERTI::ADV };
    Employee data2{ 2002117175, {"SBILHUT", "LDEXRI"}, CL::CL4, {010, 2814, 1699}, {1995,7,4}, CERTI::ADV };
    Employee data3{ 2003113260, {"HH", "LTUPF"}, CL::CL2, {010, 5798, 5383}, {1979,10,18}, CERTI::PRO };
    Employee data4{ 2008123556, {"WN", "XV"}, CL::CL1, {010, 7986, 5047}, {2010,6,14}, CERTI::PRO };
    Employee data5{ 2011125777, {"TKOQKIS", "KIM"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO };
    Employee data6{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO };
    Employee data7{ 2014130827, {"RPO", "JK"}, CL::CL4, {010, 3231, 1698}, {2009,2,1}, CERTI::ADV };
    Employee data8{ 2018117906, {"TWU", "QSOLT"}, CL::CL4, {010, 6672, 7186}, {2003,4,13}, CERTI::PRO };
    Employee data9{ 2019129568, {"SRERLALH", "HMEF"}, CL::CL2, {010, 3091, 9521}, {1999,10,1}, CERTI::PRO };

    virtual ~DbmsTest() {}

    virtual void SetUp() override {
        dbms = new Dbms(&mockDb);
        fake_db.emplace_back(&data0);
        fake_db.emplace_back(&data1);
        fake_db.emplace_back(&data2);
        fake_db.emplace_back(&data3);
        fake_db.emplace_back(&data4);
        fake_db.emplace_back(&data5);
        fake_db.emplace_back(&data6);
        fake_db.emplace_back(&data7);
        fake_db.emplace_back(&data8);
        fake_db.emplace_back(&data9);
    }

    virtual void TearDown() override {
        delete dbms;
        fake_db.clear();
    }
};

TEST_F(DbmsTest, add) {

    EXPECT_CALL(mockDb, add(_)).Times(1);
    ON_CALL(mockDb, add(_)).WillByDefault(Return(true));

    const int targetEmployeeNum = 2013059831;

    dbms->add(Employee{ targetEmployeeNum, {"Yongjun", "Kim"}, CL::CL3, {010, 3394, 4126}, {1987,6,24}, CERTI::PRO });

}

TEST_F(DbmsTest, sch_singularOutput) {

    list<Employee*> fake_queryResult;
    fake_queryResult.emplace_back(&data6);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(fake_queryResult));

    auto result = dbms->sch(Column::EMPLOYEE_NUM, "2012117017");

    EXPECT_EQ(1, result);
}

TEST_F(DbmsTest, sch_p_singularOutput) {

    list<Employee*> fake_queryResult;
    fake_queryResult.emplace_back(&data6);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(fake_queryResult));

    list<Employee> result = dbms->sch_p(Column::EMPLOYEE_NUM, "2012117017");

    ASSERT_NE(0, result.size());
    EXPECT_EQ(1, result.size());
    EXPECT_EQ(2012117017, result.front().employeeNum);
    EXPECT_EQ("LFIS", result.front().name.first);
}

TEST_F(DbmsTest, sch_multipleOutput) {

    list<Employee*> fake_queryResult1;
    fake_queryResult1.emplace_back(&data1);
    fake_queryResult1.emplace_back(&data5);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(Column::LAST_NAME, "KIM")).WillByDefault(Return(fake_queryResult1));

    list<Employee*> fake_queryResult2;
    fake_queryResult2.emplace_back(&data5);
    fake_queryResult2.emplace_back(&data9);

    ON_CALL(mockDb, search(Column::BIRTHDAY, "19991001")).WillByDefault(Return(fake_queryResult2));

    EXPECT_EQ(2, dbms->sch(Column::LAST_NAME, "KIM"));
    EXPECT_EQ(2, dbms->sch(Column::BIRTHDAY, "19991001"));
}

TEST_F(DbmsTest, sch_p_multipleOutput) {

    list<Employee*> fake_queryResult1;
    fake_queryResult1.emplace_back(&data1);
    fake_queryResult1.emplace_back(&data5);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(Column::LAST_NAME, "KIM")).WillByDefault(Return(fake_queryResult1));

    list<Employee*> fake_queryResult2;
    fake_queryResult2.emplace_back(&data5);
    fake_queryResult2.emplace_back(&data9);

    ON_CALL(mockDb, search(Column::BIRTHDAY, "19991001")).WillByDefault(Return(fake_queryResult2));

    EXPECT_EQ(2, (dbms->sch_p(Column::LAST_NAME, "KIM")).size());
    EXPECT_EQ(2, (dbms->sch_p(Column::BIRTHDAY, "19991001")).size());
}

TEST_F(DbmsTest, del) {

    list<Employee*> delTargets;
    delTargets.emplace_back(&data4);
    delTargets.emplace_back(&data5);
    delTargets.emplace_back(&data6);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(delTargets));

    EXPECT_CALL(mockDb, deleteTargets(_)).Times(1);
    ON_CALL(mockDb, deleteTargets(_)).WillByDefault(Invoke([=](list<Employee*> list) -> bool {
        for (auto e : list) {
            fake_db.remove(e);
        }

        return true;
        }));

    auto result = dbms->del(Column::CL, "CL1");

    EXPECT_EQ(delTargets.size(), result);

    auto it = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; });
    ASSERT_EQ(it, 0);
}

TEST_F(DbmsTest, del_p) {

    list<Employee*> delTargets;
    delTargets.emplace_back(&data4);
    delTargets.emplace_back(&data5);
    delTargets.emplace_back(&data6);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(delTargets));

    EXPECT_CALL(mockDb, deleteTargets(_)).Times(1);
    ON_CALL(mockDb, deleteTargets(_)).WillByDefault(Invoke([=](list<Employee*> list) -> bool {
        for (auto e : list) {
            fake_db.remove(e);
        }

        return true;
        }));

    auto result = dbms->del_p(Column::CL, "CL1");

    EXPECT_EQ(delTargets.size(), result.size());

    auto it = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; });
    ASSERT_EQ(it, 0);
}

TEST_F(DbmsTest, mod_employeeNum) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
        return (e->cl == CL::CL1) &&
            (e->employeeNum == 13059831);
        });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod(Column::CL, "CL1", Column::EMPLOYEE_NUM, "13059831");

    EXPECT_EQ(modTargets.size(), result);

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
            return (e->cl == CL::CL1) &&
                (e->employeeNum == 13059831);
            }));
}

TEST_F(DbmsTest, mod_p_employeeNum) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
        return (e->cl == CL::CL1) &&
            (e->employeeNum == 13059831);
        });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod_p(Column::CL, "CL1", Column::EMPLOYEE_NUM, "13059831");

    EXPECT_EQ(modTargets.size(), result.size());

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
            return (e->cl == CL::CL1) &&
                (e->employeeNum == 13059831);
            }));
}

TEST_F(DbmsTest, mod_certi) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return (e->cl == CL::CL1) && (e->certi == CERTI::EX); });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    int result = dbms->mod(Column::CL, "CL1", Column::CERTI, "EX");

    EXPECT_EQ(modTargets.size(), result);

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->certi == CERTI::EX; }));
}

TEST_F(DbmsTest, mod_p_certi) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return (e->cl == CL::CL1) && (e->certi == CERTI::EX); });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod_p(Column::CL, "CL1", Column::CERTI, "EX");

    EXPECT_EQ(modTargets.size(), result.size());

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->certi == CERTI::EX; }));
}

TEST_F(DbmsTest, mod_name) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return (e->cl == CL::CL1) && (e->name.first == "NO") && (e->name.last == "NAME"); });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod(Column::CL, "CL1", Column::NAME, "NO NAME");

    EXPECT_EQ(modTargets.size(), result);

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return (e->name.first == "NO") && (e->name.last == "NAME"); }));
}

TEST_F(DbmsTest, mod_p_name) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return (e->cl == CL::CL1) && (e->name.first == "NO") && (e->name.last == "NAME"); });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod_p(Column::CL, "CL1", Column::NAME, "NO NAME");

    EXPECT_EQ(modTargets.size(), result.size());

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return (e->name.first == "NO") && (e->name.last == "NAME"); }));
}

TEST_F(DbmsTest, mod_phone) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
        return (e->cl == CL::CL1) &&
            (e->phoneNum.start == 10) &&
            (e->phoneNum.mid == 1111) &&
            (e->phoneNum.last == 2222);
        });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    int result = dbms->mod(Column::CL, "CL1", Column::PHONE, "010-1111-2222");

    EXPECT_EQ(modTargets.size(), result);

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
            return (e->cl == CL::CL1) &&
                (e->phoneNum.start == 10) &&
                (e->phoneNum.mid == 1111) &&
                (e->phoneNum.last == 2222);
            }));
}

TEST_F(DbmsTest, mod_p_phone) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
        return (e->cl == CL::CL1) &&
            (e->phoneNum.start == 10) &&
            (e->phoneNum.mid == 1111) &&
            (e->phoneNum.last == 2222);
        });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod_p(Column::CL, "CL1", Column::PHONE, "010-1111-2222");

    EXPECT_EQ(modTargets.size(), result.size());

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
            return (e->cl == CL::CL1) &&
                (e->phoneNum.start == 10) &&
                (e->phoneNum.mid == 1111) &&
                (e->phoneNum.last == 2222);
            }));
}

TEST_F(DbmsTest, mod_birthday) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
        return (e->cl == CL::CL1) &&
            (e->birthDay.year == 2020) &&
            (e->birthDay.month == 2) &&
            (e->birthDay.day == 16);
        });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    int result = dbms->mod(Column::CL, "CL1", Column::BIRTHDAY, "20200216");

    EXPECT_EQ(modTargets.size(), result);

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
            return (e->cl == CL::CL1) &&
                (e->birthDay.year == 2020) &&
                (e->birthDay.month == 2) &&
                (e->birthDay.day == 16);
            }));
}

TEST_F(DbmsTest, mod_p_birthday) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data4);
    modTargets.emplace_back(&data5);
    modTargets.emplace_back(&data6);

    int cntOffset = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
        return (e->cl == CL::CL1) &&
            (e->birthDay.year == 2020) &&
            (e->birthDay.month == 2) &&
            (e->birthDay.day == 16);
        });

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    auto result = dbms->mod_p(Column::CL, "CL1", Column::BIRTHDAY, "20200216");

    EXPECT_EQ(modTargets.size(), result.size());

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        cntOffset + count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {
            return (e->cl == CL::CL1) &&
                (e->birthDay.year == 2020) &&
                (e->birthDay.month == 2) &&
                (e->birthDay.day == 16);
            }));
}



