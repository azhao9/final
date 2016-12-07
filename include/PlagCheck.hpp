#ifndef _AZNH_PLAGCHECK_HPP
#define _AZNH_PLAGCHECK_HPP

#include "Document.hpp"
#include <vector>

class PlagCheck {

	public:

		// constructor; need to specify the path for list of files
		PlagCheck(std::string f) { readNames(f); }

		// prints all file names
		std::string toString() const;

		// check with a threshold
		std::map<std::string, int> checkThreshold(int index, int threshold, unsigned n);

		// checks with high sensitivity
		std::map<std::string, int> checkH(int index);

		// checks with medium sensitivity
		std::map<std::string, int> checkM(int index);

		// checks with low sensitivity
		std::map<std::string, int> checkL(int index);

		// check through all documents
		void masterCheck(char sens);
		

	private:

		// vector containing all documents
		std::vector<Document> docs;

		// checks a specific document against others
		std::map<std::string, int> checkDoc(int index, char sens);

		// vector containing suspicious pairs of documents
		std::vector<std::string> susPairs;

		// returns a list of file paths to be read
		std::vector<std::string> readNames(std::string listFile);

		// reads files from list into docs
		void readFileList(std::string fname);

};

#endif

