#include <iostream>
#include "IOHandler.h"

void IOHandler::commandRequest(string cmd) {
	init();
	cmd_ = cmd + ";"; // ;는 문장의 끝을 의미합니다.
	try {
		parseInput();
	} 
	catch (const int& expn) {
		cout << "Command is not valid" << std::endl;
		return;
	}

	runDBMS();
	if (cmd_type_ == CMD_TYPE::ADD) return;

	runPrinter();
}

void IOHandler::init() {
	cmd_ = "";
	numRecord_ = 0;
	cmd_type_ = CMD_TYPE::NONE;
	employeeInfo_ = { 0 };
	column_.clear();
	stringInfo_.clear();
	printInfo_.clear();

	charIdx_ = 0;
	opt1_ = OPT1_TYPE::NONE;
	opt2_ = OPT2_TYPE::NONE;
	opt3_ = OPT3_TYPE::NONE;	
}

void IOHandler::runPrinter() {
	string cmdType = getCMDTypeAsString();
	if (opt1_ == OPT1_TYPE::PRINT) {
		printer_->print(printInfo_, cmdType);
	}
	else {
		printer_->print(numRecord_, cmdType);
	}
}

void IOHandler::runDBMS() {
	switch (cmd_type_) {
	case CMD_TYPE::ADD:
		dbms_->add(employeeInfo_);
		break;
	case CMD_TYPE::DEL:
		if (opt1_ == OPT1_TYPE::PRINT) {
			printInfo_ = dbms_->del_p(column_[0], stringInfo_[0]);
		}
		else {
			numRecord_ = dbms_->del(column_[0], stringInfo_[0]);
		}
		break;
	case CMD_TYPE::SCH:
		if (opt1_ == OPT1_TYPE::PRINT) {
			printInfo_ = dbms_->sch_p(column_[0], stringInfo_[0]);
		}
		else {
			numRecord_ = dbms_->sch(column_[0], stringInfo_[0]);
		}
		break;
	case CMD_TYPE::MOD:
		if (opt1_ == OPT1_TYPE::PRINT) {
			printInfo_ = dbms_->mod_p(column_[0], stringInfo_[0], column_[1], stringInfo_[1]);
		}
		else {
			numRecord_ = dbms_->mod(column_[0], stringInfo_[0], column_[1], stringInfo_[1]);
		}
		break;
	default:
		break;
	}
}

void IOHandler::setCommandType() {
	string cmd_type_str = getCMDTypeAsString();
	if (cmd_type_str == "ADD") {
		cmd_type_ = CMD_TYPE::ADD;
	}
	else if (cmd_type_str == "DEL") {
		cmd_type_ = CMD_TYPE::DEL;
	}
	else if (cmd_type_str == "SCH") {
		cmd_type_ = CMD_TYPE::SCH;
	}
	else if (cmd_type_str == "MOD") {
		cmd_type_ = CMD_TYPE::MOD;
	}
	else {
		throw invalid_argument("Command " + cmd_type_str + " is not supported");
	}
	charIdx_ = cmd_type_str.length() + SEPARATOR_LENGTH;
}

void IOHandler::parseInput() {
	setCommandType();
	parseOption1();
	parseOption2();
	parseOption3();
	switch (cmd_type_) {
	case CMD_TYPE::ADD:
		parseADD();
		break;
	case CMD_TYPE::DEL:
		parseDEL();
		break;
	case CMD_TYPE::SCH:
		parseSCH();
		break;
	case CMD_TYPE::MOD:
		parseMOD();
		break;
	default:
		break;
	}
}

static size_t extractStringBtwComma(const string& src, string& dest, size_t startIdx) {
	size_t endIdx = startIdx;
	while (src[endIdx] != ',' && src[endIdx] != ';') {
		endIdx++;
	}
	dest = src.substr(startIdx, endIdx - startIdx);
	endIdx++;

	return endIdx;
}

void IOHandler::parseOption1() {
	string opt_string;
	charIdx_ = extractStringBtwComma(cmd_, opt_string, charIdx_);
	if (opt_string == " ") {
		opt1_ = OPT1_TYPE::NONE;
	}
	else if (opt_string == "-p") {
		opt1_ = OPT1_TYPE::PRINT;
	}
	else {
		throw invalid_argument("Invalid option1");
	}
}

void IOHandler::parseOption2() {
	string opt_string;
	charIdx_ = extractStringBtwComma(cmd_, opt_string, charIdx_);
	if (opt_string == " ") {
		opt2_ = OPT2_TYPE::NONE;
	}
	else if (opt_string == "-f") {
		opt2_ = OPT2_TYPE::FIRST;
	}
	else if (opt_string == "-m") {
		opt2_ = OPT2_TYPE::MID_OR_MONTH;
	}
	else if (opt_string == "-l") {
		opt2_ = OPT2_TYPE::LAST;
	}
	else if (opt_string == "-y") {
		opt2_ = OPT2_TYPE::YEAR;
	}
	else if (opt_string == "-d") {
		opt2_ = OPT2_TYPE::DAY;
	}
	else {
		throw invalid_argument("Invalid option2");
	}
}

void IOHandler::parseOption3() {
	string opt_string;
	charIdx_ = extractStringBtwComma(cmd_, opt_string, charIdx_);
	if (opt_string == " ") {
		opt3_ = OPT3_TYPE::NONE;
	}
	else {
		throw invalid_argument("Invalid option3");
	}
}

static string IDFormatting(string ID) {
	size_t entranceYear = stoi(ID.substr(0, 2));
	if (entranceYear >= 69 && entranceYear <= 99) {
		ID = "19" + ID;
	}
	else {
		ID = "20" + ID;
	}
	return ID;
}

static void separateName(const string& fullName, string& firstName, string& lastName) {
	size_t spaceIdx = fullName.find(' ');
	if (spaceIdx == string::npos) {
		throw invalid_argument("First name and Last name should be distinguished by space character");
	}
	firstName = fullName.substr(0, spaceIdx);
	lastName = fullName.substr(spaceIdx + 1, fullName.length() - spaceIdx - 1);

	return;
}

static CL getCLEnum(const string& cl) {
	if (cl == "CL1") {
		return CL::CL1;
	}
	else if (cl == "CL2") {
		return CL::CL2;
	}
	else if (cl == "CL3") {
		return CL::CL3;
	}
	else if (cl == "CL4") {
		return CL::CL4;
	}
	else {
		throw invalid_argument("Invalid CL");
	}
}

static void separatePhoneNum(const string& fullNumber, int& start, int& mid, int& last) {
	if (fullNumber.size() != 13) {
		throw invalid_argument("Phone number should be in 010-XXXX-XXXX format");
	}
	if (fullNumber[3] != '-' ||
		fullNumber[8] != '-') {
		throw invalid_argument("Phone number should be in 010-XXXX-XXXX format");
	}
	
	start = 10;
	mid = stoi(fullNumber.substr(4, 4));
	last = stoi(fullNumber.substr(9, 4));
}


static void separateBirthDay(string birthDay,int& year, int& month, int& day) {
	if (birthDay.size() != 8) {
		throw invalid_argument("Birth day should be in YYYYMMDD format");
	}

	year = stoi(birthDay.substr(0, 4));
	month = stoi(birthDay.substr(4, 2));
	day = stoi(birthDay.substr(6, 2));
}

static CERTI getCertiEnum(string certi) {
	if (certi == "ADV") {
		return CERTI::ADV;
	}
	else if (certi == "PRO") {
		return CERTI::PRO;
	}
	else if (certi == "EX") {
		return CERTI::EX;
	}
	else {
		throw invalid_argument("Certi should be one of {ADV, PRO, EX}");
	}
}

void IOHandler::setEmployeeNum() {
	string employeeID;
	charIdx_ = extractStringBtwComma(cmd_, employeeID, charIdx_);
	employeeID = IDFormatting(employeeID);
	employeeInfo_.employeeNum = stoi(employeeID);
}
void IOHandler::setEmployeeName() {
	string fullName, firstName, lastName;
	charIdx_ = extractStringBtwComma(cmd_, fullName, charIdx_);
	separateName(fullName, firstName, lastName);
	employeeInfo_.name.first = firstName;
	employeeInfo_.name.last = lastName;
}
void IOHandler::setEmployeeCL() {
	string cl;
	charIdx_ = extractStringBtwComma(cmd_, cl, charIdx_);
	employeeInfo_.cl = getCLEnum(cl);
}
void IOHandler::setEmployeePhoneNum() {
	string phoneNum;
	int phoneNumStart, phoneNumMid, phoneNumLast;
	charIdx_ = extractStringBtwComma(cmd_, phoneNum, charIdx_);
	separatePhoneNum(phoneNum, phoneNumStart, phoneNumMid, phoneNumLast);
	employeeInfo_.phoneNum.start = phoneNumStart;
	employeeInfo_.phoneNum.mid = phoneNumMid;
	employeeInfo_.phoneNum.last = phoneNumLast;
}
void IOHandler::setEmployeeBirthday() {
	string birthDay;
	int year, month, day;
	charIdx_ = extractStringBtwComma(cmd_, birthDay, charIdx_);
	separateBirthDay(birthDay, year, month, day);
	employeeInfo_.birthDay.year = year;
	employeeInfo_.birthDay.month = month;
	employeeInfo_.birthDay.day = day;
}
void IOHandler::setEmployeeCerti() {
	string certi;
	charIdx_ = extractStringBtwComma(cmd_, certi, charIdx_);
	employeeInfo_.certi = getCertiEnum(certi);
}

void IOHandler::parseADD() {
	setEmployeeNum();
	setEmployeeName();
	setEmployeeCL();
	setEmployeePhoneNum();
	setEmployeeBirthday();
	setEmployeeCerti();
}

Column IOHandler::convertStringToColumn(string str) {
	if (str == "employeeNum") {
		return Column::EMPLOYEE_NUM;
	}
	else if (str == "name") {
		if (opt2_ == OPT2_TYPE::FIRST) return Column::FIRST_NAME;
		if (opt2_ == OPT2_TYPE::LAST) return Column::LAST_NAME;
		return Column::NAME;
	}
	else if (str == "cl") {
		return Column::CL;
	}
	else if (str == "phoneNum") {
		if (opt2_ == OPT2_TYPE::MID_OR_MONTH) return Column::PHONE_MID;
		if (opt2_ == OPT2_TYPE::LAST) return Column::PHONE_LAST;
		return Column::PHONE;
	}
	else if (str == "birthday") {
		if (opt2_ == OPT2_TYPE::YEAR) return Column::BIRTHDAY_YEAR;
		if (opt2_ == OPT2_TYPE::MID_OR_MONTH) return Column::BIRTHDAY_MONTH;
		if (opt2_ == OPT2_TYPE::DAY) return Column::BIRTHDAY_DAY;
		return Column::BIRTHDAY;
	}
	else if (str == "certi") {
		return Column::CERTI;
	}
	else {
		throw invalid_argument("Invalid column");
	}
}

Column IOHandler::convertStringToColumn2(string str) {
	if (str == "employeeNum") {
		return Column::EMPLOYEE_NUM;
	}
	else if (str == "name") {
		return Column::NAME;
	}
	else if (str == "cl") {
		return Column::CL;
	}
	else if (str == "phoneNum") {
		return Column::PHONE;
	}
	else if (str == "birthday") {
		return Column::BIRTHDAY;
	}
	else if (str == "certi") {
		return Column::CERTI;
	}
	else {
		throw invalid_argument("Invalid column");
	}
}

void IOHandler::parseDEL() {
	parseSCH();
}

void IOHandler::addColumn() {
	string colString;
	charIdx_ = extractStringBtwComma(cmd_, colString, charIdx_);
	Column col = convertStringToColumn(colString);
	column_.emplace_back(col);
}

void IOHandler::addStringData() {
	string argString;
	charIdx_ = extractStringBtwComma(cmd_, argString, charIdx_);
	stringInfo_.emplace_back(argString);
}

void IOHandler::parseSCH() {
	addColumn();
	addStringData();
}

void IOHandler::parseMOD() {
	addColumn();
	addStringData();
	addColumn();
	addStringData();
}