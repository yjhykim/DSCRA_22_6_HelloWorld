#include <iostream>
#include <fstream>
#include <string>
#include "Dbms.h"
#include "Printer.h"
#include "IOHandler.h"
using namespace std;

int main(int argc, char* argv[]) {

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if (inputFile.is_open()) {
		string line;
		Dbms dbms;
		Printer printer(outputFile);
		IOHandler io_handler(&dbms, &printer);

		while (getline(inputFile, line)) {
			io_handler.parsetInput(line);
		}
	}

	inputFile.close();
	outputFile.close();

	return 0;
}