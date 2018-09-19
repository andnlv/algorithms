#include <iostream>
#include <vector>
#include <algorithm>

int modulo = 123456789;

std::vector<int> ReadVector(std::istream &in = std::cin) {
  int size;
  in >> size;
  std::vector result(size);
  for(auto &element : result) {
    in >> element;
  }
  return result;
}

void solve(std::vector<int> elements) {
  std::sort(elements.begin(), elements.end());
  std::unique(elements.begin(), elements.end());

}


int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}