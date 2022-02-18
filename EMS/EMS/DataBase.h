#pragma once
#include "Employee.h"
#include "SearchEngine.h"
#include "Types.h"
#include "ColumnData.h"
#include <map>
#include <algorithm>

using EmployeeNum = int;

class IDataBase {
public:
    IDataBase() = default;
    ~IDataBase() = default;

    virtual list<Employee*> search(Column column, string data) = 0;

    virtual bool add(Employee target) = 0;
    virtual bool deleteTargets(list<Employee*> targets) = 0;
    virtual bool modifyTarget(EmployeeNum id, Column column, string data) = 0;
};


class DataBase : public IDataBase {
public:
    DataBase() { engine_ = new SearchEngine(); };
    ~DataBase() = default;

    void setSearchEngine(ISearchEngine* engine);

    list<Employee*> search(Column column, string data) override;

    bool add(Employee target) override;
    bool deleteTargets(list<Employee*> targets) override;
    bool modifyTarget(EmployeeNum id, Column column, string data) override;

private:
    std::map<EmployeeNum, Employee> database_;
    SearchEngine* engine_;
};
