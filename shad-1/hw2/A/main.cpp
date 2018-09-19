#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

std::array<std::vector<int>, 2> readInput(std::istream &in = std::cin) {
  std::uint16_t size;
  std::array<std::vector<int>, 2> seqences;
  for (auto &cur_secuence : seqences) {
    in >> size;
    cur_secuence.resize(size);
    for (int i = 0; i < size; ++i) {
      in >> cur_secuence[i];
    }
  }
  return seqences;
}

int solve(const std::array<std::vector<int>, 2> &seqences) {
  std::vector<std::vector<int>> table(seqences[0].size() + 1);
  for (auto &line : table) {
    line.resize(seqences[1].size() + 1);
  }
  for (uint16_t i = 0; i < seqences[0].size(); ++i) {
    table[i][0] = 0;
  }
  for (uint16_t j = 0; j < seqences[1].size(); ++j) {
    table[0][j] = 0;
  }
  for (uint16_t i = 1; i <= seqences[0].size(); ++i) {
    for (uint16_t j = 1; j <= seqences[1].size(); ++j) {
      auto tmp = table[i - 1][j - 1] + static_cast<int>(seqences[0][i - 1] == seqences[1][j - 1]);
      table[i][j] = std::max({table[i - 1][j], table[i][j - 1], tmp});
    }
  }
  return table[seqences[0].size()][seqences[1].size()];
}

int main() {
  std::cout << solve(readInput());
  return 0;
}
