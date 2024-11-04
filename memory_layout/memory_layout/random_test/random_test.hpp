/*
 * Initial code for TESTCASE
 * file : random_test.hpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 07.9.2024
 */
#ifndef RANDOM_TEST_HPP
#define RANDOM_TEST_HPP

#include <vector>

#include "../memory_layout/memory_layout.hpp"
#include "../memory_layout/text/declaration.hpp"

class RandomTest {
  // class friend test
  friend class ListDelarations;

 public:
  RandomTest(int from, int to);

  void runTest();
  void compareOutputs();

 private:
  int from;
  int to;

  // ANSI escape codes for colors
  const std::string green = "\033[32m";
  const std::string red = "\033[31m";
  const std::string cyan = "\033[36m";
  const std::string reset = "\033[0m";  // To reset to default color

  bool compareFiles(const std::string &file1, const std::string &file2);
};

#endif  // RANDOM_TEST_HPP