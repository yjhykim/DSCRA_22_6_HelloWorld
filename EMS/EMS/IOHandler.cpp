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

void IOHandler::runDBMS() {
	switch (cmd_type) {
	case ADD:
		dbms->add(employeeInfo);
		break;
	case DEL:
		dbms->del(column[0], stringInfo[0]);
		break;
	case SCH:
		dbms->sch(column[0], stringInfo[0]);
		break;
	case MOD:
		dbms->mod(column[0], stringInfo[0], column[1], stringInfo[1]);
		break;
	default:
		break;
	}
}

void IOHandler::setCommandType() {
	string cmd_type_str = cmd.substr(0, 3);
	if (cmd_type_str == "ADD") {
		cmd_type = ADD;
	}
	else if (cmd_type_str == "DEL") {
		cmd_type = DEL;
	}
	else if (cmd_type_str == "SCH") {
		cmd_type = SCH;
	}
	else if (cmd_type_str == "MOD") {
		cmd_type = MOD;
	}
	else {
		throw invalid_argument("Command " + cmd_type_str + " is not supported");
	}
}

void IOHandler::parseInput() {
	setCommandType();

	switch (cmd_type) {
	case ADD:
		parseADD();
		break;
	case DEL:
		parseDEL();
		break;
	case SCH:
		parseSCH();
		break;
	case MOD:
		parseMOD();
		break;
	default:
		break;
	}
}

void IOHandler::parseADD() {

}
void IOHandler::parseDEL() {

}
void IOHandler::parseSCH() {

}
void IOHandler::parseMOD() {

}