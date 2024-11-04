#include "memory_layout.hpp"

MemoryManager::MemoryManager(string fileName) {
  ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << fileName << " for reading."
              << std::endl;
  }
  string s;
  getline(file, s);
  this->listDelarations = new ListDelarations(stoi(s));
  getline(file, s);
  this->listDelarations->push(s);
  // TODO 
}

string MemoryManager::toString_ListDeclarations() {
  return this->listDelarations->str();
}

MemoryManager::~MemoryManager() {
  // TODO
  // for (int i=0;i<size;i++){delete [i] listDelarations;}
  // delete [] listDelarations;
}