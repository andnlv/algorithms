#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>

void read_input(size_t &size, std::vector<int> &seq, std::istream &in = std::cin) {
  in >> size;
  seq.resize(size);
  for (size_t i = 0; i < size; ++i) {
    in >> seq[i];
  }
}

void write_answer(const std::vector<int> &answer, std::ostream &out = std::cout) {
  for (auto i: answer) {
    out << i << " ";
  }
  out << "\n";
}

struct table_struct {
  int value;
  int prev;
  size_t depth;
};

bool isBetter(std::vector<std::array<table_struct, 2>> &table,
              int first_index, int second_index, int first_sign, int second_sign) {
  if (table[first_index][first_sign].depth != table[second_index][second_sign].depth) {
    return table[first_index][first_sign].depth > table[second_index][second_sign].depth;
  }
  bool result = false;
  while (first_index != second_index) {
    result = first_index < second_index;
    first_index = table[first_index][first_sign].prev;
    second_index = table[second_index][second_sign].prev;
    first_sign = 1 - first_sign;
    second_sign = 1 - second_sign;
  }
  return result;
}

void solver(const size_t &size, const std::vector<int> &seq, std::vector<int> &answer) {
  std::vector<std::array<table_struct, 2>> table(size);
  for (int index = 0; index < static_cast<int>(size); ++index) {
    table[index][0] = table[index][1] = {seq[index], -1, 1};
    for (int j = index - 1; j >= 0; --j) {
      if (table[j][0].value < seq[index] && (table[index][1].prev == -1 ||
          isBetter(table, j, table[index][1].prev, 0, 0))) {
        table[index][1] = {seq[index], j, table[j][0].depth + 1};
      }
      if (table[j][1].value > seq[index] && (table[index][0].prev == -1 ||
          isBetter(table, j, table[index][0].prev, 1, 1))) {
        table[index][0] = {seq[index], j, table[j][1].depth + 1};
      }
    }
  }

  int sign = 0;
  int id = 0;
  for (auto i = static_cast<int>(size - 1); i >= 0; --i) {
    for (int j = 0; j < 2; ++j) {
      if (isBetter(table, i, id, j, sign)) {
        id = i;
        sign = j;
      }
    }
  }
  answer.resize(table[id][sign].depth);
  for (int i = static_cast<int>(answer.size()) - 1; i >= 0; --i) {
    answer[i] = table[id][sign].value;
    id = table[id][sign].prev;
    sign = 1 - sign;
  }
}

/*
bool vector_equal(std::vector<int> &a, std::vector<int> &b) {
  if(a.size() != b.size()) {
    return false;
  }
  for(int i = 0; i < (int)a.size(); ++i) {
    if(a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

std::vector<int> generate_input(int n, int k, std::mt19937 &generator) {
  std::uniform_int_distribution<int> randint(0, k);
  std::vector<int> result(static_cast<size_t>(n));
  for(int i = 0; i < n; ++i) {
    result[i] = randint(generator);
  }
  return result;
}

void print_vector(std::vector<int> v) {
  for(auto a : v) {
    std:: cout << a << " ";
  }
  std::cout << "\n";
}

void ranom_test() {
  int n, k, m;
  std::cin >> n >> k >> m;
  std::vector<int> result;
  std::vector<int> result2;
  std::mt19937 generator;
  for(int i = 0; i < m; ++i) {
    std::vector<int> seq = generate_input(n, k, generator);
    solver(size_t(n), seq, result);
    stupied_solver(size_t(n), seq, result2);
    if(!vector_equal(result, result2)) {
      std::cout << "ERROR!\n";
      print_vector(seq);
      print_vector(result);
      print_vector(result2);
      std:: cout << "\n";
    }
  }
}
*/
void solve() {
  size_t size;
  std::vector<int> sequence;
  std::vector<int> answer;
  read_input(size, sequence);
  solver(size, sequence, answer);
  write_answer(answer);
}

int main() {
  solve();
  // ranom_test();
  return 0;
}
