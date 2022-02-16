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

        Employee data1{ 1910127115, {"KBU", "KIM"}, CL::CL3, {010, 3284, 4054}, {1966,8,14}, CERTI::ADV };
        Employee data2{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO };
        Employee data3{ 2011125777, {"TKOQKIS", "KIM"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO };
        Employee data4{ 2019129568, {"SRERLALH", "HMEF"}, CL::CL2, {010, 3091, 9521}, {1999,10,1}, CERTI::PRO };
        Employee data5{ 2018117906, {"TWU", "QSOLT"}, CL::CL4, {010, 6672, 7186}, {2003,4,13}, CERTI::PRO };
    
        virtual ~DbmsTest() {}

        virtual void SetUp() override {
            dbms = new Dbms(&mockDb);

            fake_db.emplace_back(&data1);
            fake_db.emplace_back(&data2);
            fake_db.emplace_back(&data3);
            fake_db.emplace_back(&data4);
            fake_db.emplace_back(&data5);
        }


        virtual void TearDown() override {
            delete dbms;
            fake_db.clear();
        }
};

TEST_F(DbmsTest, add_positive) {

    EXPECT_CALL(mockDb, add(_)).Times(1);
    ON_CALL(mockDb, add(_)).WillByDefault(Return(true));

    const int targetEmployeeNum = 2013059831;

    dbms->add(Employee{ targetEmployeeNum, {"Yongjun", "Kim"}, CL::CL3, {010, 3394, 4126}, {1987,6,24}, CERTI::PRO });

}

TEST_F(DbmsTest, sch_singularOutput) {

    list<Employee*> fake_queryResult;
    fake_queryResult.emplace_back(&data2);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(fake_queryResult));

    list<Employee*> result = dbms->sch(Column::EMPLOYEE_NUM, "2012117017");

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front()->employeeNum, 2012117017);
    EXPECT_EQ(result.front()->name.first, "LFIS");
}

TEST_F(DbmsTest, sch_multipleOutput) {

    list<Employee*> fake_queryResult;
    fake_queryResult.emplace_back(&data1);
    fake_queryResult.emplace_back(&data3);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(fake_queryResult));

    list<Employee*> result = dbms->sch(Column::LAST_NAME, "KIM");

    EXPECT_EQ(dbms->sch(Column::LAST_NAME, "KIM").size(), 2);
    EXPECT_EQ(dbms->sch(Column::BIRTHDAY, "19991001").size(), 2);
}

TEST_F(DbmsTest, del_positive) {

    list<Employee*> delTargets;
    delTargets.emplace_back(&data2);
    delTargets.emplace_back(&data3);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(delTargets));

    EXPECT_CALL(mockDb, deleteTargets(_)).Times(1);
    ON_CALL(mockDb, deleteTargets(_)).WillByDefault(Invoke([=](list<Employee*> list) -> bool {
        for (auto e : list) {
            fake_db.remove(e);
        }

        return true;
    }));

    list<Employee*> result = dbms->del(Column::CL, "CL1");

    EXPECT_EQ(result.size(), delTargets.size());

    auto it = count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; });
    ASSERT_EQ(it, 0);
}

TEST_F(DbmsTest, mod_positive) {

    list<Employee*> modTargets;
    modTargets.emplace_back(&data2);
    modTargets.emplace_back(&data3);

    EXPECT_CALL(mockDb, search(_, _)).Times(AnyNumber());
    ON_CALL(mockDb, search(_, _)).WillByDefault(Return(modTargets));

    EXPECT_CALL(mockDb, deleteTargets(_)).Times(1);
    ON_CALL(mockDb, deleteTargets(_)).WillByDefault(Return(true));

    list<Employee*> result = dbms->mod(Column::CL, "CL1", Column::CERTI, "EX");

    EXPECT_EQ(result.size(), modTargets.size());

    EXPECT_EQ(count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->cl == CL::CL1; }),
        count_if(fake_db.begin(), fake_db.end(), [](Employee* e) {return e->certi == CERTI::EX; }));
}
