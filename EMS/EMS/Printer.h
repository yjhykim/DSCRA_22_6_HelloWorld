#pragma once

#include "Employee.h"
#include <list>
#include <string>

class IPrinter {
public:
    virtual void print(list<Employee*> data, string cmd) const = 0;
};

class ShortPrinter : public IPrinter {
public:
    void print(list<Employee*> data, string cmd) const override;
};

class DetailedPrinter : public IPrinter {
public:
    void print(list<Employee*> data, string cmd) const override;
};
