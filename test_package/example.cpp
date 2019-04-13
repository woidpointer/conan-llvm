#include <iostream>

#include <clang/Basic/Version.h>


int main() {

  std::string v = clang::getClangFullVersion();
  std::cout << "Clang: " << v << '\n';
  return 0;
}
