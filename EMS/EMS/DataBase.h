#pragma once

#include "Employee.h"

class IDataBase {
public:
	virtual ~IDataBase() {}

};

class DataBase : public IDataBase {


};