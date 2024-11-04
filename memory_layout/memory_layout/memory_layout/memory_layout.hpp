// memory_layout.hpp
#ifndef MEMORY_LAYOUT_HPP
#define MEMORY_LAYOUT_HPP

#include "text/declaration.hpp"

class MemoryManager {
 public:
  MemoryManager(string fileName);

  ~MemoryManager();

  string toString_ListDeclarations();

 private:
  ListDelarations *listDelarations;
};

#endif  // MEMORY_LAYOUT_HPP