#pragma once
#include "../EMS/DataBase.h"
#include "gmock/gmock.h"

class MockDataBase : public IDataBase {
public:
    MOCK_METHOD(list<Employee*>, search, (Column column, string data), (override));
    MOCK_METHOD(bool, add, (Employee target), (override));
    MOCK_METHOD(bool, deleteTargets, (list<Employee*> targets), (override));
    MOCK_METHOD(bool, modifyTarget, (EmployeeNum id, Column column, string data), (override));
};
