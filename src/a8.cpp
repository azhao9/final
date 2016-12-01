#include <iostream>
#include <sstream>
#include <string>
#include "Document.hpp"

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

	Document doc("../data/sonnet_1.txt");
	doc.addTextFromFile(2);

	doc.addTextFromFile(4);

	std::cout << doc.toString(4);

	return 0;
}
