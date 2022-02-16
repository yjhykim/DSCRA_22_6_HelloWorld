#include <iostream>
#include "IOHandler.h"

void IOHandler::commandRequest(const string& cmd) {
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
	string cmd_type_str = cmd.substr(0, 3);
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
	charIdx = 3+1; // CMD,[ ],
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
	while (src[endIdx] != ',') {
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

void IOHandler::parseADD() {
	Employee newEmployee;
	newEmployee.employeeNum = 18050301;
	newEmployee.name.first = "KYUMOK";
	newEmployee.name.last = "KIM";
	newEmployee.cl = CL::CL2;
	newEmployee.phoneNum.start = 10;
	newEmployee.phoneNum.mid = 9777;
	newEmployee.phoneNum.last = 6055;
	newEmployee.birthDay.year = 1998;
	newEmployee.birthDay.month = 9;
	newEmployee.birthDay.day = 6;
	newEmployee.certi = CERTI::PRO;

	employeeInfo = newEmployee;
}

void IOHandler::parseDEL() {

}

void IOHandler::parseSCH() {

}

void IOHandler::parseMOD() {

}