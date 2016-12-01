#ifndef _AZNH_PLAGCHECK_HPP
#define _AZNH_PLAGCHECK_HPP

#include "Document.hpp"
#include <vector>

class PlagCheck {

	public:

		// constructor; need to specify the path for list of files
		PlagCheck(std::string f) : { readFiles(f); }

		// prints all file names
		std::string toString() const;

	private:

		// vector containing all documents
		std::vector<Document> docs;

		// reads files from a file containing paths into vector of documents
		void readFiles(std::string path);

};

#endif
