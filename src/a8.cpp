#include <iostream>
#include <sstream>
#include <string>
#include "LanguageModel.hpp"

/* nice, safe C++ method to convert a string to an integer */
int readInt(char *str) {
  int n;
  std::stringstream ss(str);
  ss >> n;
  if (ss.fail()) {
    std::cerr << "Error: failed to convert string to integer!\n";
    return 0;
  }
  return n;
}

/* function to print how to call this program */
void printUsage() {
    std::cout << "Usage: a8 [input file] [n-gram size] [a|r|c|g] [docs to generate]\n";
}

/* main: parse arguments, call appropriate functions */
int main(int argc, char** argv) {
  if (argc < 4 || (std::string(argv[3]) == "g" && argc < 5)) {
    printUsage();
    return 1;
  }

  std::string inputName(argv[1]);
  int n = readInt(argv[2]);

  LanguageModel lm(n);
  lm.readFileList(inputName);
  
  if (std::string(argv[3]) == "g") { // if we get "g" we need to generate text
    int genCount = readInt(argv[4]);
    std::cout << "Generated text:\n";
    for (int i=0; i<genCount; ++i) {
      std::cout << lm.generateText() << "\n";
    }
  } else if (std::string(argv[3]) == "a" || std::string(argv[3]) == "r" || std::string(argv[3]) == "c") {
    std::cout << lm.toString(argv[3][0]); // print the model
  } else { // got something other than a|r|c|g, so print usage and give up 
    printUsage();
    return 1;
  }

  return 0;
}
