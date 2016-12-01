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

	private:

		// vector containing all documents
		std::vector<Document> docs;

		// returns a list of file paths to be read
		std::vector<std::string> readNames(std::string listFile);

		// reads files from list into docs
		void readFileList(std::string fname);

};

#endif

