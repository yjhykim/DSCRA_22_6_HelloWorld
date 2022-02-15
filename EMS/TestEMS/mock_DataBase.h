#pragma once
#include "../EMS/DataBase.h"
#include "gmock/gmock.h"

class MockDataBase : public IDataBase {
public:
    MOCK_METHOD(std::list<Employee*>, search, (string data));
    MOCK_METHOD(bool, add, (Employee target));
    MOCK_METHOD(bool, deleteTargets, (list<Employee*> targets));
};
