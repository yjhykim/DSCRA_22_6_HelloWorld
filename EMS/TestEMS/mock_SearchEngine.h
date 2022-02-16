#pragma once

#include "pch.h"
#include "../EMS/SearchEngine.h"

class MockSearchEngine : public ISearchEngine
{
public:
    MOCK_METHOD(list<Employee*>, search, (list<Employee*>& db, int employeeNum), (const, override));
    MOCK_METHOD(list<Employee*>, search, (list<Employee*>& db, Name& name), (const, override));
    MOCK_METHOD(list<Employee*>, search, (list<Employee*>& db, CL cl), (const, override));
    MOCK_METHOD(list<Employee*>, search, (list<Employee*>& db, PhoneNum& phoneNum), (const, override));
    MOCK_METHOD(list<Employee*>, search, (list<Employee*>& db, CERTI certi), (const, override));
};
