#include <iostream>
#include "IOHandler.h"

void IOHandler::commandRequest(string _cmd) {
	cmd = _cmd + ";"; // ;는 문장의 끝을 의미합니다.
	try {
		parseInput();
	} 
	catch (int expn) {
		cout << "Command is not valid" << std::endl;
		return;
	}

	runDBMS();
	runPrinter();
}

void IOHandler::runPrinter() {
	string cmdType = getCMDTypeAsString();
	printer->print(printInfo, cmdType);
}

void IOHandler::runDBMS() {
	switch (cmd_type) {
	case CMD_TYPE::ADD:
		dbms->add(employeeInfo);
		break;
	case CMD_TYPE::DEL:
		printInfo = dbms->del(column[0], stringInfo[0]);
		break;
	case CMD_TYPE::SCH:
		printInfo = dbms->sch(column[0], stringInfo[0]);
		break;
	case CMD_TYPE::MOD:
		printInfo = dbms->mod(column[0], stringInfo[0], column[1], stringInfo[1]);
		break;
	default:
		break;
	}
}

void IOHandler::setCommandType() {
	string cmd_type_str = getCMDTypeAsString();
	if (cmd_type_str == "ADD") {
		cmd_type = CMD_TYPE::ADD;
	}
	else if (cmd_type_str == "DEL") {
		cmd_type = CMD_TYPE::DEL;
	}
	else if (cmd_type_str == "SCH") {
		cmd_type = CMD_TYPE::SCH;
	}
	else if (cmd_type_str == "MOD") {
		cmd_type = CMD_TYPE::MOD;
	}
	else {
		throw invalid_argument("Command " + cmd_type_str + " is not supported");
	}
	charIdx = 3+1;
}

void IOHandler::parseInput() {
	setCommandType();
	parseOption1();
	parseOption2();
	parseOption3();
	switch (cmd_type) {
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
	charIdx = extractStringBtwComma(cmd, opt_string, charIdx);
	if (opt_string == "") {
		opt1 = OPT1_TYPE::NONE;
	}
	else if (opt_string == "-p") {
		opt1 = OPT1_TYPE::PRINT;
	}
	else {
		throw invalid_argument("Invalid option1");
	}
}

void IOHandler::parseOption2() {
	string opt_string;
	charIdx = extractStringBtwComma(cmd, opt_string, charIdx);
	if (opt_string == "") {
		opt2 = OPT2_TYPE::NONE;
	}
	else if (opt_string == "-f") {
		opt2 = OPT2_TYPE::FIRST;
	}
	else if (opt_string == "-m") {
		opt2 = OPT2_TYPE::MID_OR_MONTH;
	}
	else if (opt_string == "-l") {
		opt2 = OPT2_TYPE::LAST;
	}
	else if (opt_string == "-y") {
		opt2 = OPT2_TYPE::YEAR;
	}
	else if (cmd.substr(charIdx, 2) == "-D") {
		opt2 = OPT2_TYPE::DAY;
	}
	else {
		throw invalid_argument("Invalid option2");
	}
}

void IOHandler::parseOption3() {
	string opt_string;
	charIdx = extractStringBtwComma(cmd, opt_string, charIdx);
	if (opt_string == "") {
		opt3 = OPT3_TYPE::NONE;
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
		return CL::CL1;
	}
	else if (cl == "CL3") {
		return CL::CL1;
	}
	else if (cl == "CL4") {
		return CL::CL1;
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
	
	start = 010;
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

void IOHandler::parseADD() {

	string employeeID;
	charIdx = extractStringBtwComma(cmd, employeeID, charIdx);
	employeeID = IDFormatting(employeeID);
	employeeInfo.employeeNum = stoi(employeeID);
	
	string fullName, firstName, lastName;
	charIdx = extractStringBtwComma(cmd, fullName, charIdx);
	separateName(fullName, firstName, lastName);
	employeeInfo.name.first = firstName;
	employeeInfo.name.last = lastName;

	string cl;
	charIdx = extractStringBtwComma(cmd, cl, charIdx);
	employeeInfo.cl = getCLEnum(cl);

	string phoneNum;
	int phoneNumStart, phoneNumMid, phoneNumLast;
	charIdx = extractStringBtwComma(cmd, phoneNum, charIdx);
	separatePhoneNum(phoneNum, phoneNumStart, phoneNumMid, phoneNumLast);
	employeeInfo.phoneNum.start = phoneNumStart;
	employeeInfo.phoneNum.mid = phoneNumMid;
	employeeInfo.phoneNum.last = phoneNumLast;


	string birthDay;
	int year, month, day;
	charIdx = extractStringBtwComma(cmd, birthDay, charIdx);
	separateBirthDay(birthDay, year, month, day);
	employeeInfo.birthDay.year = year;
	employeeInfo.birthDay.month = month;
	employeeInfo.birthDay.day = day;

	string certi;
	charIdx = extractStringBtwComma(cmd, certi, charIdx);
	employeeInfo.certi = getCertiEnum(certi);
}

Column IOHandler::convertStringToColumn(string str) {
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
		if (opt2 == OPT2_TYPE::MID_OR_MONTH) return Column::PHONE_MID;
		if (opt2 == OPT2_TYPE::LAST) return Column::PHONE_LAST;
		return Column::PHONE;
	}
	else if (str == "birthDay") {
		if (opt2 == OPT2_TYPE::YEAR) return Column::BIRTHDAY_YEAR;
		if (opt2 == OPT2_TYPE::MID_OR_MONTH) return Column::BIRTHDAY_MONTH;
		if (opt2 == OPT2_TYPE::DAY) return Column::BIRTHDAY_DAY;
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

void IOHandler::parseSCH() {
	string colString;
	charIdx = extractStringBtwComma(cmd, colString, charIdx);
	Column col = convertStringToColumn(colString);
	column.emplace_back(col);
	string argString;
	charIdx = extractStringBtwComma(cmd, argString, charIdx);
	stringInfo.emplace_back(argString);
}

void IOHandler::parseMOD() {
	string colString1;
	charIdx = extractStringBtwComma(cmd, colString1, charIdx);
	Column col1 = convertStringToColumn(colString1);
	column.emplace_back(col1);
	string argString1;
	charIdx = extractStringBtwComma(cmd, argString1, charIdx);
	stringInfo.emplace_back(argString1);

	string colString2;
	charIdx = extractStringBtwComma(cmd, colString2, charIdx);
	Column col2 = convertStringToColumn(colString2);
	column.emplace_back(col2);
	string argString2;
	charIdx = extractStringBtwComma(cmd, argString2, charIdx);
	stringInfo.emplace_back(argString2);
}