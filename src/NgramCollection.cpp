#include "NgramCollection.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

/* take iterators to the start/end of an Ngram, increment the appropriate
 * element of the map */
void NgramCollection :: increment(std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end) {
	assert(end - begin == n); // make sure we've got the right number of words
	std::string last = *(end-1); // pull off the word at the end
	std::vector<std::string> words; // make a vector containing the first n-1 words
	for (auto i = begin; i != end-1; ++i) {
		words.push_back(*i);
	}
	counts[words][last] += 1; // increment the corresponding count
}

/* toString method; calls one of three versions depending on the
 * parameter value */
std::string NgramCollection :: toString(char order) const {
	switch (order) {
		case 'a':
			return toStringAlpha();
		case 'r':
			return toStringReverseAlpha();
		case 'c':
			return toStringCount();
		default:
			std::cerr << "Error: toString() given a bad argument!\n";
	}
	return "";
}

/* return the model as string in alpha-sorted order */
std::string NgramCollection :: toStringAlpha() const {
	std::stringstream ss;
	for (auto &i : counts) {
		for (auto &end : i.second) {
			for (auto &word : i.first) {
				ss << word << " ";
			}
			ss << end.first << " " << end.second << "\n";
		}
	}
	return ss.str();
}

/* return the model as string in reverse alpha-sorted order */
std::string NgramCollection :: toStringReverseAlpha() const {
	std::stringstream ss;
	for (auto i = counts.rbegin(); i != counts.rend(); ++i) {
		for (auto j = i->second.rbegin(); j != i->second.rend(); ++j) {
			for (auto &word : i->first) {
				ss << word << " ";
			}
			ss << j->first << " " << j->second << "\n";
		}
	}
	return ss.str();
}

/* return the model as string in reverse count order */
std::string NgramCollection :: toStringCount() const {
	std::stringstream ss;

	/* A small "nested class" (shown as a possible alternative to using std::tuple).
	 * Note that this class will go out of scope at the end of this method.
	 */
	class NgramRecord {
		public:
			// constructor
			NgramRecord(unsigned c, std::vector<std::string>n) : count(c), ngram(n) { }

			// member variables
			unsigned count;
			std::vector<std::string> ngram;

			// comparison operator
			bool operator< (const NgramRecord &other) {
				if (this->count != other.count) { // first try to sort by count
					return (this->count < other.count);
				} else { // if the counts are equal, sort based on the words instead
					return (this->ngram < other.ngram);
				}
			}
	};

	std::vector<NgramRecord> recs; // we need to pull out the entries in the model so we can sort them

	for (auto &i : counts) { // loop over pairs in the outer map
		for (auto &end : i.second) { // loop over pairs in the inner map
			std::vector<std::string> ngram;
			for (auto &word : i.first) {
				ngram.push_back(word); // make a vector of the first n-1 words
			}
			ngram.push_back(end.first); // add the last word
			recs.push_back({end.second, ngram}); // add a record with the appropriate count and ngram
		}
	}

	std::sort(recs.begin(), recs.end()); // sort using the < operator for class NgramRecord

	for(auto &t : recs) { // loop through (sorted) list
		for (auto &v : t.ngram) { // print each word of the ngram
			ss << v << " ";
		}
		ss << t.count << "\n"; // then print the count
	}
	return ss.str();
}

