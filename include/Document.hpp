#ifndef _AZNH_DOCUMENT_HPP
#define _AZNH_DOCUMENT_HPP
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include "NgramCollection.hpp"

class Document {

	public:

		// constructor; need to specify N and path of file
		Document(std::string p) : path(p) { }

		// print the model to a string ('a'=alpha, 'r'=reverse-alpha, 'c'=count)
		std::string toString(unsigned n) const;

		// add text from the path for a given length n
		void addTextFromFile(unsigned n);

	private:
		// add ngrams to the model from a vector of words
		void buildNgrams(unsigned n, const std::vector<std::string> &text);

		// maps from N to the NgramCollection
		std::map<unsigned, NgramCollection> NgramCollections;

		std::string path;
};

#endif
