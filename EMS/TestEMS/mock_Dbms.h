#pragma once

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../EMS/Dbms.h"

class mock_Dbms : public IDbms {
public:
	MOCK_METHOD(void, add, (Employee data), (override));
	MOCK_METHOD(list<Employee*>, del, (Column type, string data), (override));
	MOCK_METHOD(list<Employee*>, sch, (Column type, string data), (override));
	MOCK_METHOD(list<Employee*>, mod, (Column typeFrom, string dataFrom, Column typeTo, string dataTo), (override));
};