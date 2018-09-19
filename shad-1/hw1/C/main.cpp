#include <algorithm>
#include <iostream>
#include <vector>

class Cube {
 private:
  int a_, b_, c_;
 public:
  explicit Cube(int x_l, int y_l, int z_l) {
    a_ = x_l;
    b_ = y_l;
    c_ = z_l;
  }

  bool operator<(const Cube &other) const {
    return a_ < other.a_ && b_ < other.b_ && c_ < other.c_;
  }
};

void read_input(std::vector<Cube> &cubes, std::istream &in = std::cin) {
  int number;
  in >> number;
  cubes.clear();
  for (int i = 0; i < number; ++i) {
    int a_l, b_l, c_l;
    in >> a_l >> b_l >> c_l;
    cubes.emplace_back(a_l, b_l, c_l);
  }
}

void solver(std::vector<Cube> &cubes) {
  std::vector<int> table(cubes.size(), 1);
  for (size_t i = 1; i < cubes.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (cubes[j] < cubes[i] && table[j] >= table[i]) {
        ++table[i];
      }
    }
  }
  std::cout << *std::max_element(table.begin(), table.end());
}

int main() {
  std::vector<Cube> cubes;
  read_input(cubes);
  solver(cubes);
  return 0;
}
