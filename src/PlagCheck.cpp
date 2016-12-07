#include "PlagCheck.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

/* 
 * Accepts a file containing paths to documents
 * Reads each file into a Document object
 * For each Document, add an i-gram collection of the parsed text
 * Adds each Document object into the docs vector
 */
void PlagCheck :: readFileList(std::string fname) {
	std::vector<std::string> nameList = readNames(fname);
	for (std::string &name : nameList) {
		Document doc (name);
		for(unsigned i = 2; i < 15; i++) {
			// checks if i is shorter than length of entire document
			if (i < doc.length()) {
				doc.addTextFromFile(i);
			}
		}
		docs.push_back(doc);
	}
}

/* 
 * Reads from a file containing paths to documents
 * Adds paths to a vector of strings and returns this vector
 */
std::vector<std::string> PlagCheck :: readNames(std::string listFile) {
	std::vector<std::string> names;
	std::ifstream fin(listFile); // try to open file
	if (!fin.is_open()) { // see if it worked
		std::cerr << "Error: failed to open listfile '" << listFile << "'\n";
		exit(-1);
	}

	std::string name;
	while (fin >> name) {
		names.push_back(name); // read names until we run out of file
	}
	fin.close(); // close the file
	return names;
}

void PlagCheck :: masterCheck(char sens) {

	for (size_t i = 0; i < docs.size(); i++) {
		checkDoc(i, sens);
	}
}

void PlagCheck :: checkDoc(int index, char sens) {

	if (sens == 'H') {
		checkH(index);
	} else if (sens == 'M') {
		checkM(index); 
	} else if (sens == 'L') {
		checkL(index);
	}
}


void PlagCheck :: checkL(int index) {

	Document thisDoc = docs.at(index);
	std::map<unsigned, NgramCollection> thisGrams = thisDoc.getGrams();

	// document does not contain any 8-grams, assume it can't be plagiarized
	if (thisGrams.find(8) == thisGrams.end()) {
		return;
	}

	NgramCollection this8gram = thisGrams.at(8);
	auto this8gramCounts = this8gram.getCounts();

	for (unsigned j = index+1; j < docs.size(); j++) {

		Document curDoc = docs.at(j);

		std::map<unsigned, NgramCollection> curGrams = curDoc.getGrams();
		
		// document to compare to does not contain any 8-grams, assume can't be plagiarized from
		if (curGrams.find(8) == curGrams.end()) {
			continue;
		}

		NgramCollection cur8gram = curGrams.at(8);	
		auto cur8gramCounts = cur8gram.getCounts();

	}

}

void PlagCheck :: checkM(int index) {

}

void PlagCheck :: checkH(int index) {

}















