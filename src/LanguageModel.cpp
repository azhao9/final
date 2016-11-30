#include "LanguageModel.hpp"
#include <iostream>
#include <fstream>

/* read a list of names from a file, add each document to the model */
void LanguageModel :: readFileList(std::string fname) {
  std::vector<std::string> nameList = readNames(fname);
  for (std::string &name : nameList) {
    addTextFromFile(name);
  }
}


/* read a list of names from a file */
std::vector<std::string> LanguageModel :: readNames(std::string listFile) {
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


/* add text from the given document file to the model */
void LanguageModel :: addTextFromFile(std::string fname) {
  std::ifstream fin(fname);
  if (!fin.is_open()) { // make sure it opened
    std::cerr << "Error: could not open file '" << fname << "', file will be skipped...\n";
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


/* generate a new document based on the current model;
 * returns the new document as a single string
 */
std::string LanguageModel :: generateText() const {
  std::string doc;
  
  std::list<std::string> curr; // context (i.e. current (n-1)gram)
  for (unsigned i=1; i<ngrams.getN(); ++i) {
    curr.push_back("<START_" + std::to_string(i) + ">"); // prime the pump with start tags
    doc += " " + curr.back();
  }

  std::string next;
  std::string end = "<END_" + std::to_string(ngrams.getN()-1) + ">"; // what we're looking for
  do { // add words to the document until we see the final end tag
    next = ngrams.pickWord(curr.begin(), curr.end());
    doc += next + " ";
    curr.pop_front();
    curr.push_back(next);
  } while (next != end);

  return doc;
}
