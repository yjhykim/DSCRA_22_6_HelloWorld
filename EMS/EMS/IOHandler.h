#pragma once

#include <vector>
using namespace std;
#include "Dbms.h"
#include "Printer.h"

class IOHandler {
public:
	virtual ~IOHandler() {}
	IOHandler() :dbms(nullptr), printer(nullptr) {}
	IOHandler(IDbms* _dbms, IPrinter* _printer) : dbms(_dbms), printer(_printer) {}

	void commandRequest(string cmd) {}
private:
	void parsetInput(string cmd) {}
	IDbms* dbms;
	IPrinter* printer;
};