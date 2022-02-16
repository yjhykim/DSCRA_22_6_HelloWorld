#pragma once

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../EMS/Dbms.h"

class mock_Dbms : public IDbms {
public:
	MOCK_METHOD(void, add, (Employee data), (override));
	MOCK_METHOD(int, del, (Column type, string data), (override));
	MOCK_METHOD(list<Employee*>, del_p, (Column type, string data), (override));
	MOCK_METHOD(int, sch, (Column type, string data), (override));
	MOCK_METHOD(list<Employee*>, sch_p, (Column type, string data), (override));
	MOCK_METHOD(int, mod, (Column typeFrom, string dataFrom, Column typeTo, string dataTo), (override));
	MOCK_METHOD(list<Employee*>, mod_p, (Column typeFrom, string dataFrom, Column typeTo, string dataTo), (override));
};