#ifndef _BEN_CS120_LANGUAGE_MODEL_HPP
#define _BEN_CS120_LANGUAGE_MODEL_HPP
#include <vector>
#include <string>
#include <cassert>
#include "NgramCollection.hpp"

class LanguageModel {

public:

  // constructor; need to specify N
  LanguageModel(int n) : ngrams(n) { assert(n > 1); }

  // takes name of a file that contains paths to the documents
  void readFileList(std::string fname);

  // add text from the given filename to the model
  void addTextFromFile(std::string fname);

  // print the model to a string ('a'=alpha, 'r'=reverse-alpha, 'c'=count)
  std::string toString(char order ='a') const;

  // generate a new document string from the model
  std::string generateText() const;

private:
  // read a list of paths from a file
  std::vector<std::string> readNames(std::string listFile);
  // add ngrams to the model from a vector of words
  void buildNgrams(const std::vector<std::string> &text);
  
  // stores actual ngram-count information
  NgramCollection ngrams;
};

#endif
