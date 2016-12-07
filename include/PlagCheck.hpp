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

		// checks with high sensitivity
		void checkH(int index);

		// checks with medium sensitivity
		void checkM(int index);

		// checks with low sensitivity
		void checkL(int index);

		// checks a specific document against others
		void checkDoc(int index, char sens);

		// check through all documents
		void masterCheck(char sens);
		

	private:

		// vector containing all documents
		std::vector<Document> docs;

		// vector containing suspicious pairs of documents
		std::vector<std::string> susPairs;

		// returns a list of file paths to be read
		std::vector<std::string> readNames(std::string listFile);

		// reads files from list into docs
		void readFileList(std::string fname);

};

#endif

