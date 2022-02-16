#pragma once
#include "Employee.h"
#include "SearchEngine.h"
#include "Types.h"
#include "ColumnData.h"
#include <list>
#include <algorithm>

class IDataBase {
public:
    IDataBase() = default;
    ~IDataBase() = default;

    virtual list<Employee*> search(Column column, string data) = 0;

    virtual bool add(Employee target) = 0;
    virtual bool deleteTargets(list<Employee*> targets) = 0;
};


class DataBase : public IDataBase {
public:
    DataBase() { engine_ = new SearchEngine(); };
    ~DataBase() = default;

    list<Employee*> search(Column column, string data) override;

    bool add(Employee target) override;
    bool deleteTargets(list<Employee*> target) override;

private:
    std::list<Employee*> database_;
    SearchEngine* engine_;
};
