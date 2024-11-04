// declaration.h
#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "../../main.hpp"

class Type {
 public:
  virtual string nameType() const = 0;
  virtual int sizeType() const = 0;
};

class IntegerType : public Type {
 public:
  string nameType() const { return "IntegerType()"; }
  int sizeType() const { return 4; }
};

class LongType : public Type {
 public:
  string nameType() const { return "LongType()"; }
  int sizeType() const { return 8; }
};

class CharacterType : public Type {
 public:
  string nameType() const { return "CharacterType()"; }
  int sizeType() const { return 1; }
};

class ArrayType : public Type {
 private:
  int sizeArray;
  Type *typeArray;

 public:
  ArrayType(int sizeArray, Type *typeArray)
      : sizeArray(sizeArray), typeArray(typeArray) {}
  string nameType() const {
    return "Array(" + to_string(sizeArray) + "," + typeArray->nameType() + ')';
  }
  int sizeType() const { return 1; }
};

class Declaration {
 protected:
  string name;

 public:
  Declaration(string name) : name(name) {}
  virtual string str() = 0;
};

class NewDeclaration : public Declaration {
 private:
  Type *type;

 public:
  NewDeclaration(string name, Type *type) : Declaration(name), type(type) {}
  string str() {
    return "InitDeclaration(" + name + "," + type->nameType() + ')';
  }
  ~NewDeclaration() { delete type; }
};

class CallDeclaration : public Declaration {
 public:
  CallDeclaration(string name) : Declaration(name) {}
  string str() { return "CallDeclaration(" + name + ')'; }
};

class DeleteDeclaration : public Declaration {
 public:
  DeleteDeclaration(string name) : Declaration(name) {}
  string str() { return "DeleteDeclaration(" + name + ')'; }
};

class ListDelarations {
 private:
  Declaration **listDelarations;
  int size;
  int sizeMax;

 public:
  ListDelarations(int sizeMax);
  void push(string declaration);
  string str() const;
};

#endif  // DECLARATION_HPP