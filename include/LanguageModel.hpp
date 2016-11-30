#ifndef _BEN_CS120_LANGUAGE_MODEL_HPP
#define _BEN_CS120_LANGUAGE_MODEL_HPP
#include <vector>
#include <string>
#include <cassert>
#include "NgramCollection.hpp"

class LanguageModel {

public:

  // constructor; need to specify N and path of file
  LanguageModel(int n, std::string p) : ngrams(n), path(p) { assert(n > 1); }

  // print the model to a string ('a'=alpha, 'r'=reverse-alpha, 'c'=count)
  std::string toString(char order ='c') const;

private:
  // add ngrams to the model from a vector of words
  void buildNgrams(const std::vector<std::string> &text);

  // add text from the path
  void addTextFromFile();
  
  // stores actual ngram-count information
  NgramCollection ngrams;

  std::string path;
};

#endif
