/*
 * Initial code for TESTCASE
 * file : unit_test.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 07.9.2024
 */
#include "unit_test.hpp"
map<string, bool (UnitTest::*)()> UnitTest::TESTS;

bool UnitTest::function1() {
  // data
  ListDelarations list(1);
  list.push("Call VoTien");

  // expect
  string expect = "[\n\tCallDeclaration(VoTien)\n]";

  // output
  string output = list.str();

  // remove data

  // prit result
  if (expect == output) {
    cout << green << "test function 1 --------------- PASS" << reset << "\n";
    return true;
  } else {
    cout << red << "test function 1 --------------- FAIL" << reset << "\n";
    cout << "\texpect : " << expect << endl;
    cout << "\toutput : " << output << endl;
    return false;
  }
}

bool UnitTest::function2() {
  // data
  ListDelarations *list = new ListDelarations(2);
  list->push("Call VoTien");

  // expect
  string expect = "[\n\tCallDeclaration(VoTien)\n]";

  // output
  string output = list->str();

  // remove data
  delete list;

  // prit result
  if (expect == output) {
    cout << green << "test function 2 --------------- PASS" << reset << "\n";
    return true;
  } else {
    cout << red << "test function 2 --------------- FAIL" << reset << "\n";
    cout << "- expect : " << expect << endl;
    cout << "- output : " << output << endl;
    return false;
  }
}

bool UnitTest::function3() {
  // data
  ListDelarations *list = new ListDelarations(3);
  list->push("Call VoTien");

  // expect
  string expect = "[\n\tCallDeclaration(VoTien)\n]";

  // output
  string output = list->str();

  // remove data
  delete list;

  // prit result
  if (expect == output) {
    cout << green << "test function 3 --------------- PASS" << reset << "\n";
    return true;
  } else {
    cout << red << "test function 3 --------------- FAIL" << reset << "\n";
    cout << "- expect : " << expect << endl;
    cout << "- output : " << output << endl;
    return false;
  }
}