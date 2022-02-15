#pragma once
#include "../EMS/Printer.h"
#include "gmock/gmock.h"

class MockPrinter : public IPrinter {
public:
    MOCK_METHOD(void, print, (std::list<Employee*> data));
};
