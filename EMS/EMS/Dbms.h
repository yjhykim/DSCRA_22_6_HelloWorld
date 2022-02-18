#pragma once

#include "Employee.h"
#include "DataBase.h"
#include <list>

using namespace std;



class IDbms {
public:
	virtual ~IDbms() {}
	virtual void add(Employee data) = 0;
	virtual int del(Column type, string data) = 0;
	virtual list<Employee> del_p(Column type, string data) = 0;
	virtual int sch(Column type, string data) = 0;
	virtual list<Employee> sch_p(Column type, string data) = 0;
	virtual int mod(Column typeFrom, string dataFrom, Column typeTo, string dataTo) = 0;
	virtual list<Employee> mod_p(Column typeFrom, string dataFrom, Column typeTo, string dataTo) = 0;
};

class Dbms : public IDbms {
public:
	Dbms(IDataBase* db);
	virtual void add(Employee data) override;
	virtual int del(Column type, string data) override;
	virtual list<Employee> del_p(Column type, string data) override;
	virtual int sch(Column type, string data) override;
	virtual list<Employee> sch_p(Column type, string data) override;
	virtual int mod(Column typeFrom, string dataFrom, Column typeTo, string dataTo) override;
	virtual list<Employee> mod_p(Column typeFrom, string dataFrom, Column typeTo, string dataTo) override;

private:
	IDataBase* db_;
};
