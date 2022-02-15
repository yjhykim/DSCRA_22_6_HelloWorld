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

	vector<string> parsetInput(string cmd) {
		vector<string> cmd_args;
		cmd_args.emplace_back("ADD");
		cmd_args.emplace_back("-");
		return cmd_args;
	}
private:
	IDbms* dbms;
	IPrinter* printer;
};