#include "main.hpp"

//!  build g++ -o main -Iinclude -std=c++17 main.cpp
//! run : ./main
int main(int argc, char* argv[]) {
  xt::xarray<double> a = {{1., 2.}, {3., 4.}};
  std::cout << a << std::endl;

  xt::xtensor<double, 2> b = {{1., 2.}, {3., 4.}};
  std::cout << b << std::endl;

  xt::xtensor_fixed<double, xt::xshape<2, 2>> c = {{1., 2.}, {3., 4.}};
  std::cout << c << std::endl;
  return 0;
}