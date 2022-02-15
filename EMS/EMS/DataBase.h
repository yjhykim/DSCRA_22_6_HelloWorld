#pragma once
#include <list>
#include "Employee.h"
#include "SearchEngine.h"
#include "Dbms.h"

class IDataBase {
public:
    virtual list<Employee*> search(Column column, string data) = 0;

    virtual bool add(Employee target) = 0;
    virtual bool deleteTargets(list<Employee*> targets) = 0;
};

class DataBase : public IDataBase {
public:
    list<Employee*> search(Column column, string data) override;

    bool add(Employee target) override;
    bool deleteTargets(list<Employee*> targets) override;

private:
    std::list<Employee> database_;
    // SearchEngine& engine;
};
