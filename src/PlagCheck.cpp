#include "PlagCheck.hpp"
#include <iostream>
#include <fstream>

void PlagCheck :: readFileList(std::string fname) {
    std::vector<std::string> nameList = readNames(fname);
    for (std::string &name : nameList) {
      Document doc (name);
      for(unsigned i = 2; i < 8; i++) {
          doc.addTextFromFile(i);
      }
      docs.push_back(doc);
    }
}

std::vector<std::string> PlagCheck :: readNames(std::string listFile) {
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

