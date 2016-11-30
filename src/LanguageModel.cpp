#include "LanguageModel.hpp"
#include <iostream>
#include <fstream>

/* add text from the given document file to the model */
void LanguageModel :: addTextFromFile() {
  std::ifstream fin(path);
  if (!fin.is_open()) { // make sure it opened
    std::cerr << "Error: could not open file '" << path << "', file will be skipped...\n";
    return;
  }

  std::string word;
  std::vector<std::string> text; // the document will be stored here
  for (unsigned i=1; i<ngrams.getN(); i++) {
    text.push_back("<START_" + std::to_string(i) + ">"); // add n-1 start tags
  }
  while (fin >> word) {
    text.push_back(word); // read words from the file and add them to the document 
  }
  for (unsigned i=1; i<ngrams.getN(); i++) {
    text.push_back("<END_" + std::to_string(i) + ">"); // add n-1 end tags
  }
  fin.close(); // close the file

  buildNgrams(text); // add ngrams from the document to the model
}


/* takes a document (as a vector of words, including start/end tags), and
 * adds each n-gram to the model */
void LanguageModel :: buildNgrams(const std::vector<std::string> &text) {
  auto first = text.begin(); // first element
  auto last = text.begin() + ngrams.getN(); // n-1th element

  while (last-1 != text.end()) {
    ngrams.increment(first, last); // add ngrams until we run out
    ++first;
    ++last;
  }
}

/* toString just returns whatever the NgramCollection toString() gives us */
std::string LanguageModel :: toString(char order) const {
   return ngrams.toString(order);
}

