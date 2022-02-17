#pragma once

#include <vector>
#include <stdexcept>
using namespace std;
#include "Dbms.h"
#include "Printer.h"

class IOHandler {
	enum class CMD_TYPE { NONE, ADD, DEL, SCH, MOD };
	enum class OPT1_TYPE { NONE, PRINT };
	enum class OPT2_TYPE { NONE, FIRST, MID_OR_MONTH, LAST, YEAR, DAY };
	enum class OPT3_TYPE { NONE, RESERVED };
public:
	IOHandler(IDbms* _dbms, IPrinter* _printer) : 
		cmd(""), cmd_type( CMD_TYPE::NONE ), employeeInfo({ 0 }), charIdx(0), numRecord(0),
		opt1(OPT1_TYPE::NONE), opt2(OPT2_TYPE::NONE), opt3(OPT3_TYPE::NONE), 
		dbms(_dbms), printer(_printer) {}

	virtual ~IOHandler() {
		delete dbms;
		delete printer;
	}

	void commandRequest(string _cmd);

private:
	void parseInput();
	void setCommandType();
	void parseOption1();
	void parseOption2();
	void parseOption3();
	void parseADD();
	void parseDEL();
	void parseSCH();
	void parseMOD();
	void runDBMS();
	void runPrinter(); 
	string getCMDTypeAsString() {
		return cmd.substr(0, 3);
	}

	Column convertStringToColumn(string str);

	string cmd;
	int numRecord;
	CMD_TYPE cmd_type;
	Employee employeeInfo;
	vector<Column> column;
	vector<string> stringInfo;
	list<Employee> printInfo;

	size_t charIdx;
	OPT1_TYPE opt1;
	OPT2_TYPE opt2;
	OPT3_TYPE opt3;

	IDbms* dbms;
	IPrinter* printer;
};