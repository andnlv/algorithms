#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> read_input(std::istream &in = std::cin) {
  int arrays_count, elements_count;
  in >> arrays_count >> elements_count;
  std::vector<std::vector<int>> table(arrays_count, std::vector<int>(elements_count));
  for (int i = 0; i < arrays_count; ++i) {
    for (int j = 0; j < elements_count; ++j) {
      in >> table[i][j];
    }
  }
  return table;
}

void print_table(std::vector<std::vector<int>> &table) {
  for (auto &line : table) {
    for (auto element : line) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }
}

std::vector<int> solve(const std::vector<std::vector<int>> &table, int begin, int end) {
  std::vector<int> result;
  if (end - begin == 1) {
    result = std::move(table[begin]);
  } else {
    std::vector<int> result_f = solve(table, begin, (begin + end) / 2);
    std::vector<int> result_s = solve(table, (begin + end) / 2, end);
    result.resize(result_f.size() + result_s.size());
    std::merge(result_f.begin(), result_f.end(), result_s.begin(), result_s.end(), result.begin());
  }
  return result;
}

/*
std::vector<int> generate_array(int m, int l) {
  std::random_device generator;
  std::uniform_int_distribution<int64_t> random(0, l);
  std::vector<int> result;
  for (int i = 0; i < m; ++i) {
    result.push_back(random(generator));
  }
  std::sort(result.begin(), result.end());
  return result;
}

std::stringstream generate_input(int n, int m, int l) {
  std::stringstream input;
  input << n << " " << m << "\n";
  for(int i = 0; i < n; ++i) {
    for(auto x : generate_array(m, l)) {
      input << x << " ";
    }
    input << "\n";
  }
  return input;
}

bool check_answer(const std::vector<int> &result) {
  for(int i = 1; i < result.size(); ++i) {
    if(result[i - 1] > result[i]) {
      return false;
    }
  }
  return true;
}

void test() {
  int n, m, l, t;
  std::cin >> n >> m >> l >> t;
  for(int i = 0; i < t; ++i) {
    auto in = generate_input(n, m, l);
    std::string wrong_in = in.str();
    std::vector<std::vector<int>> input = read_input(in);
    time_t t = clock();
    std::vector<int> result = solve(input, 0, n);
    std::cout << double(clock() - t) / CLOCKS_PER_SEC << "\n";
    if(!check_answer(result)) {
      std::cout << wrong_in;
    }
  }
}
 */

void run() {
  std::vector<std::vector<int>> input = read_input();
  auto result = solve(input, 0, input.size());
  for (int i = 0; i < static_cast<int>(result.size()); ++i) {
    std::cout << result[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  run();
  // test();
  return 0;
}
