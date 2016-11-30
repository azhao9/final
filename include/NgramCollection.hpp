#ifndef _CS120_NGRAM_COLLECTION_HPP
#define _CS120_NGRAM_COLLECTION_HPP
#include <vector>
#include <list>
#include <map>
#include <string>
#include <cassert>

class NgramCollection {

public:

  //Generate an NgramCollection object with N equal to argument num
  NgramCollection(unsigned num) : n(num) { assert(n > 1);  }

  //Increase count for NgramCollection representing values from begin up to end
  //begin is an iterator to the first word in the Ngram,
  //end is an iterator to the end of the Ngram
  // (so (end - begin) == N)
  void increment(std::vector<std::string>::const_iterator begin,
		 std::vector<std::string>::const_iterator end);

  //Retrieve the string representation of this NgramCollection (one entry per line) in specified order
  std::string toString(char order ='c') const; // will default to count
  // specialized print-sorted functions
  std::string toStringAlpha() const;
  std::string toStringReverseAlpha() const;
  std::string toStringCount() const;

private:

  //the collection of entries in this NgramCollection
  std::map<std::vector<std::string>, std::map<std::string, unsigned>> counts;

  //the number of items in our NgramCollection
  unsigned n;  
};

#endif
