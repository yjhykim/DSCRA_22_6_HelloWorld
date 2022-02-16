
#include "pch.h"
#include "../EMS/IOHandler.h"
#include "mock_Dbms.h"
#include "mock_Printer.h"
#include "mock_DataBase.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Test;

mock_Dbms mockDBMS;
MockPrinter mockPrinter;
IOHandler* ioHandler;
list<Employee*> fakeDB;

Employee data1{ 1910127115, {"KBU", "KIM"}, CL::CL3, {010, 3284, 4054}, {1966,8,14}, CERTI::ADV };
Employee data2{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO };
Employee data3{ 2011125777, {"TKOQKIS", "KIM"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO };
Employee data4{ 2019129568, {"SRERLALH", "HMEF"}, CL::CL2, {010, 3091, 9521}, {1999,10,1}, CERTI::PRO };
Employee data5{ 2018117906, {"TWU", "QSOLT"}, CL::CL4, {010, 6672, 7186}, {2003,4,13}, CERTI::PRO };

class IOHandlerTest : public testing::Test {
public:

	virtual ~IOHandlerTest() {}

	virtual void SetUp() override {
		ioHandler = new IOHandler(&mockDBMS, &mockPrinter);
		fakeDB.emplace_back(&data1);
		fakeDB.emplace_back(&data2);
		fakeDB.emplace_back(&data3);
		fakeDB.emplace_back(&data4);
		fakeDB.emplace_back(&data5);
	}


	virtual void TearDown() override {
		delete ioHandler;
		fakeDB.clear();
	}
};

TEST(IOHandlerTest, ADD) {
	EXPECT_CALL(mockDBMS, add(_)).Times(1);
	ioHandler->commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
}

TEST(IOHandlerTest, DEL) {

	list<Employee*> localFakeQueryResult;
	localFakeQueryResult.emplace_back(&data2);

	EXPECT_CALL(mockDBMS, del(_,_)).Times(1);
	ON_CALL(mockDBMS, del(_,_)).WillByDefault(Return(localFakeQueryResult));
	ioHandler->commandRequest("DEL,,,,name,JJIVL LFIS");
}

TEST(IOHandlerTest, SCH) {
	list<Employee*> localFakeQueryResult;
	localFakeQueryResult.emplace_back(&data2);

	EXPECT_CALL(mockDBMS, sch(_, _)).Times(1);
	ON_CALL(mockDBMS, sch(_, _)).WillByDefault(Return(localFakeQueryResult));
	ioHandler->commandRequest("DEL,,,,name,JJIVL LFIS");
}

TEST(IOHandlerTest, MOD) {
	list<Employee*> localFakeQueryResult;
	localFakeQueryResult.emplace_back(&data2);

	EXPECT_CALL(mockDBMS, mod(_, _, _, _)).Times(1);
	ON_CALL(mockPrinter, print(localFakeQueryResult,string("MOD"))).WillByDefault(Return(localFakeQueryResult));
	ioHandler->commandRequest("MOD,,,,name,JJIVL LFIS,name KKIVL KFIS");
}

TEST(IOHandlerTest, PRINT) {
	list<Employee*> localFakeQueryResult;
	localFakeQueryResult.emplace_back(&data2);

	ON_CALL(mockDBMS, mod(_, _, _, _)).WillByDefault(Return(localFakeQueryResult));
	EXPECT_CALL(mockPrinter, print(_, string("MOD"))).Times(1);
	ioHandler->commandRequest("MOD,,,,name,JJIVL LFIS,name KKIVL KFIS");
}
