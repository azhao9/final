#include "PlagCheck.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

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

/* Checks for plagiarism for a certain threshold number of times
*/
std::map<std::string, int> PlagCheck :: checkThreshold(int index, int threshold) {

	// this document
	Document thisDoc = docs.at(index);
	std::map<unsigned, NgramCollection> thisGrams = thisDoc.getGrams();

	// use a map for constant time access
	std::map<std::string, int> badPairs;

	// document does not contain any 9-grams, assume it can't be plagiarized
	if (thisGrams.find(9) == thisGrams.end()) {
		return badPairs;
	}

	NgramCollection this9gram = thisGrams.at(9);
	auto this9gramCounts = this9gram.getCounts();

	// avoids checking pairs that were checked already
	for (unsigned j = index+1; j < docs.size(); j++) {

		int violations = 0;

		Document curDoc = docs.at(j);

		std::map<unsigned, NgramCollection> curGrams = curDoc.getGrams();

		// document to compare to does not contain any 9-grams, assume can't be plagiarized from
		if (curGrams.find(9) == curGrams.end()) {
			continue;
		}

		NgramCollection cur9gram = curGrams.at(9);	
		auto cur9gramCounts = cur9gram.getCounts();

		for (auto &grams : this9gramCounts) {
			std::vector<std::string> length8string = grams.first;

			if (cur9gramCounts.find(length8string) != cur9gramCounts.end()) {
				// suspicious, this doc contains an identical 8 word string as cur

				violations++;

				if (violations >= threshold) {
					// passed the threshold, flag this document as suspicious
					std::string susDocPair = thisDoc.getPath() + " " + curDoc.getPath();

					badPairs[susDocPair] = 1;
					// done with this current doc, go to next
					break;

				}

			}
		}

	}

	return badPairs;
}

void PlagCheck :: checkL(int index) {

}

void PlagCheck :: checkM(int index) {

}

void PlagCheck :: checkH(int index) {

}



