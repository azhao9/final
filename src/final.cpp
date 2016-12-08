#include <iostream>
#include <sstream>
#include <string>
#include "Document.hpp"
#include "PlagCheck.hpp"

/* nice, safe C++ method to convert a string to an integer */
int readInt(char *str) {
	int n;
	std::stringstream ss(str);
	ss >> n;
	if (ss.fail()) {
		std::cerr << "Error: failed to convert string to integer!\n";
		return 0;
	}
	return n;
}

/* function to print how to call this program */
void printUsage() {
	std::cout << "Usage: a8 [input file] [n-gram size] [a|r|c|g] [docs to generate]\n";
}

/* main: parse arguments, call appropriate functions */
int main(int argc, char** argv) {

	if (argc == 1) {

		std::cout << "Must specify a file containing paths\n";
		return 1;

	}

	// file name
	std::string arg1(argv[1]);

	PlagCheck p(arg1);

	if (argc == 2) {
		// default to medium sensitivity

		p.masterCheck('M');
	} else {

		char sens = argv[2][0];
		p.masterCheck(sens);
	}
	return 0;
}
