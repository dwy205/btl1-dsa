#include "declaration.hpp"

ListDelarations::ListDelarations(int sizeMax) {
  listDelarations = new Declaration *[sizeMax];
  size = 0;
  this->sizeMax = sizeMax;
}

/*
 * Type name (Type : Integer, Long, Character, Integer[1,2] )
 * Call name
 * Delete name
 */
void ListDelarations::push(string declaration) {
  stringstream ss(declaration);
  string keyword, name;
  ss >> keyword >> name;

  listDelarations[size++] = new CallDeclaration(name);
  //TODO
  while (size==sizeMax){break;}
}

string ListDelarations::str() const {
  if (this->size == 0) return "[]";
  string result = "";
  for (int i = 0; i < this->size - 1; i++) {
    result += this->listDelarations[i]->str() + "\n\t";
  }
  return "[\n\t" + result + this->listDelarations[this->size - 1]->str() +
         "\n]";
}