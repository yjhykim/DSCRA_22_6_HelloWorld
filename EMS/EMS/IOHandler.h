#pragma once

#include <vector>
#include <stdexcept>
using namespace std;
#include "Dbms.h"
#include "Printer.h"

class IOHandler {
	enum CMD_TYPE { NONE, ADD, DEL, SCH, MOD};
public:
	virtual ~IOHandler() {}
	IOHandler(IDbms* _dbms, IPrinter* _printer) : cmd(""), cmd_type( NONE ), employeeInfo({ 0 }), charIdx( 0 ), dbms(_dbms), printer(_printer) {}

	void commandRequest(const string& cmd);
private:
	void parseInput();
	void setCommandType();
	void parseADD();
	void parseDEL();
	void parseSCH();
	void parseMOD();
	void runDBMS();
	void runPrinter();

	string cmd;
	CMD_TYPE cmd_type;
	Employee employeeInfo;
	vector<Column> column;
	vector<string> stringInfo;
	list<Employee*> printInfo;

	unsigned int charIdx;

	IDbms* dbms;
	IPrinter* printer;
};