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
	IOHandler(IDbms* dbms, IPrinter* printer) : 
		cmd_(""), cmd_type_( CMD_TYPE::NONE ), employeeInfo_({ 0 }), charIdx_(0), numRecord_(0),
		opt1_(OPT1_TYPE::NONE), opt2_(OPT2_TYPE::NONE), opt3_(OPT3_TYPE::NONE), 
		dbms_(dbms), printer_(printer) {}

	virtual ~IOHandler() {
		delete dbms_;
		delete printer_;
	}

	void commandRequest(string cmd);

private:
	void init();
	void parseInput();
	void setCommandType();
	void parseOption1();
	void parseOption2();
	void parseOption3();
	void setEmployeeNum();
	void setEmployeeName();
	void setEmployeeCL();
	void setEmployeePhoneNum();
	void setEmployeeBirthday();
	void setEmployeeCerti();
	void parseADD();
	void parseDEL();
	void addColumn();
	void addStringData();
	void parseSCH();
	void parseMOD();
	void runDBMS();
	void runPrinter(); 
	string getCMDTypeAsString() {
		return cmd_.substr(0, 3);
	}

	Column convertStringToColumn(string str);
	Column convertStringToColumn2(string str);

	string cmd_;
	int numRecord_;
	CMD_TYPE cmd_type_;
	Employee employeeInfo_;
	vector<Column> column_;
	vector<string> stringInfo_;
	list<Employee> printInfo_;

	size_t charIdx_;
	OPT1_TYPE opt1_;
	OPT2_TYPE opt2_;
	OPT3_TYPE opt3_;

	IDbms* dbms_;
	IPrinter* printer_;
};