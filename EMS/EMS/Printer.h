#pragma once

#include "Employee.h"
#include <list>
#include <string>
#include <fstream>


class IPrinter {
public:
    ~IPrinter() {}
    virtual void print(list<Employee>& data, string& cmd) const = 0;
    virtual void print(int data, string& cmd) const = 0;
};

class Printer : public IPrinter {
public:
    Printer(ofstream& output) : output_(output) {}
    ~Printer() {}
    void print(list<Employee>& data, string& cmd) const;
    void print(int data, string& cmd) const;
private:
    ofstream& output_;
};

