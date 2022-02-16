#include "pch.h"
#include "../EMS/IOHandler.h"
#include "mock_Dbms.h"
#include "mock_Printer.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Test;

TEST(IOHandler_test1, ADD) {
	mock_Dbms dbms;
	EXPECT_CALL(dbms, add(_)).Times(1);
	MockPrinter printer;
	IOHandler io_handler(&dbms, &printer);
	io_handler.commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
}

TEST(IOHandler_test1, DEL) {
	mock_Dbms dbms;
	EXPECT_CALL(dbms, del(_,_)).Times(1);
	MockPrinter printer;
	IOHandler io_handler(&dbms, &printer);
	io_handler.commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
	io_handler.commandRequest("ADD,,,,18050302,SAMSUNG KIM,CL2,010-9777-6056,19980907,ADV");
	io_handler.commandRequest("DEL,,,,name,KYUMOK KIM");
}

TEST(IOHandler_test1, SCH) {
	mock_Dbms dbms;
	EXPECT_CALL(dbms, sch(_,_)).Times(1);
	MockPrinter printer;
	IOHandler io_handler(&dbms, &printer);
	io_handler.commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
	io_handler.commandRequest("ADD,,,,18050302,SAMSUNG KIM,CL3,010-9777-6056,19980907,ADV");
	io_handler.commandRequest("SCH,,,,cl,CL2");
}

TEST(IOHandler_test1, MOD) {
	mock_Dbms dbms;
	EXPECT_CALL(dbms, mod(_,_,_,_)).Times(1);
	MockPrinter printer;
	IOHandler io_handler(&dbms, &printer);
	io_handler.commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
	io_handler.commandRequest("ADD,,,,18050302,SAMSUNG KIM,CL2,010-9777-6056,19980907,ADV");
	io_handler.commandRequest("MOD,,,,phoneNum,010-9777-6055,birthday,20000906");
}

TEST(IOHandler_test2, SHORT_PRINT) {
	mock_Dbms dbms;
	EXPECT_CALL(dbms, sch(_,_)).Times(1);
	MockPrinter printer;
	IOHandler io_handler(&dbms, &printer);
	io_handler.commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
}

TEST(IOHandler_test2, DETAILED_PRINT) {
	mock_Dbms dbms;
	EXPECT_CALL(dbms, sch(_,_)).Times(1);
	MockPrinter printer;
	IOHandler io_handler(&dbms, &printer);
	io_handler.commandRequest("ADD,,,,18050301,KYUMOK KIM,CL2,010-9777-6055,19980906,PRO");
}