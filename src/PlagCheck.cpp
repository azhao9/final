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
		for(unsigned i = 2; i < 30; i++) {
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
		for (auto & el : checkDoc(i, sens)) {
			std::cout << el.first << "\n";
		}
	}
}

std::map<std::string, int> PlagCheck :: checkDoc(int index, char sens) {

	if (sens == 'H') {
		return checkH(index);
	} else if (sens == 'M') {
		return checkM(index); 
	} else {
		return checkL(index);
	}
}

/* Checks for plagiarism for a certain threshold number of times, and a length of gram
*/
std::map<std::string, int> PlagCheck :: checkThreshold(int index, int threshold, unsigned n) {

	// this document
	Document thisDoc = docs.at(index);
	std::map<unsigned, NgramCollection> thisGrams = thisDoc.getGrams();

	// use a map for constant time access
	std::map<std::string, int> badPairs;

	// document does not contain any n-grams, assume it can't be plagiarized
	if (thisGrams.find(n) == thisGrams.end()) {
		return badPairs;
	}

	NgramCollection thisNgram = thisGrams.at(n);
	auto thisNgramCounts = thisNgram.getCounts();

	// avoids checking pairs that were checked already
	for (unsigned j = index+1; j < docs.size(); j++) {

		int violations = 0;

		Document curDoc = docs.at(j);

		std::map<unsigned, NgramCollection> curGrams = curDoc.getGrams();

		// document to compare to does not contain any n-grams, assume can't be plagiarized from
		if (curGrams.find(n) == curGrams.end()) {
			continue;
		}

		NgramCollection curNgram = curGrams.at(n);	
		auto curNgramCounts = curNgram.getCounts();

		for (auto &grams : thisNgramCounts) {
			std::vector<std::string> lengthN_1string = grams.first;

			if (curNgramCounts.find(lengthN_1string) != curNgramCounts.end()) {

				// suspicious, this doc contains an identical N-1 word string as cur
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

std::map<std::string, int> PlagCheck :: checkL(int index) {

	std::map<std::string, int> m;

	return m;

}

std::map<std::string, int> PlagCheck :: checkM(int index) {

	std::map<std::string, int> m;

	return m;

}

std::map<std::string, int> PlagCheck :: checkH(int index) {

	return checkThreshold(index, 10, 10);

}



