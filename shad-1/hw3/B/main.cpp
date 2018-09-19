#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <list>
#include <random>

class Hash {
 private:
  int a_, b_, c_;
 public:
  Hash() {
    std::random_device generator;
    auto rand_int = std::uniform_int_distribution<int>(1, 1024);
    a_ = rand_int(generator);
    b_ = rand_int(generator);
    c_ = rand_int(generator);
  }
  size_t operator()(std::array<int, 3> array) {
    return a_ * static_cast<size_t >(array[0]) +
        b_ * static_cast<size_t >(array[1]) +
        c_ * static_cast<size_t >(array[2]);
  }
};

template<class Key>
class HashSet {
 private:
  std::vector<std::list<Key>> container_;
  Hash hash_;
  size_t size_;
  const double max_load_factor = 2;
  const double resize_factor = 2;

 public:
  HashSet()
      : container_(1),
        size_(0) {};

  void insert(const Key &key) {
    std::list<Key> &bucket = container_[hash_(key) % container_.size()];
    if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
      bucket.push_back(key);
      ++size_;
    }
    if (size_ > container_.size() * max_load_factor) {
      this->resize(static_cast<size_t >(container_.size() * resize_factor));
    }
  }

  size_t size() const {
    return size_;
  }

  void resize(size_t new_size) {
    std::vector<std::list<Key>> new_container(new_size);
    std::swap(this->container_, new_container);
    size_ = 0;
    for (const auto &bucket : new_container) {
      for (const auto &key : bucket) {
        this->insert(key);
      }
    }
  }
};

int NOD_of_three(int first, int second, int third) {
  while (first != 0 && second != 0 && third != 0) {
    if (first <= second && first <= third) {
      second %= first;
      third %= first;
      continue;
    }
    if (second <= first && second <= third) {
      first %= second;
      third %= second;
      continue;
    }
    if (third <= second && third <= first) {
      second %= third;
      first %= third;
      continue;
    }
  };
  if (first == 0) {
    first = third;
  }
  if (second == 0) {
    second = third;
  }
  while (first != 0 && second != 0) {
    if (first <= second) {
      second %= first;
    } else {
      first %= second;
    }
  }
  return std::max(first, second);
}

std::vector<std::array<int, 3>> ReadInput(std::istream &in = std::cin) {
  int size;
  in >> size;
  std::vector<std::array<int, 3>> triangles(size);
  for (auto &triangle : triangles) {
    for (auto &side : triangle) {
      in >> side;
    }
    std::sort(triangle.begin(), triangle.end());
    int nod = NOD_of_three(triangle[0], triangle[1], triangle[2]);
    triangle[0] /= nod;
    triangle[1] /= nod;
    triangle[2] /= nod;
  }
  return triangles;
};

size_t Solve(const std::vector<std::array<int, 3>> &triangles) {
  HashSet<std::array<int, 3>> hash_table;
  for (const auto &triangle : triangles) {
    hash_table.insert(triangle);
  }
  return hash_table.size();
}

void PrintAnswer(size_t answer) {
  std::cout << answer;
}

void run() {
  PrintAnswer(Solve(ReadInput()));
}

/*

std::vector<std::array<int, 3>> generate_input(int n, int k) {
  static std::random_device generator;
  auto rand_int = std::uniform_int_distribution<int>(1, k);
  std::vector<std::array<int, 3>> result(n);
  for (auto &triangle : result) {
    for (auto &side : triangle) {
      side = rand_int(generator);
    }
  }
  return result;
};

void test() {
  int n, k, m;
  std::cin >> n >> k >> m;
  for (int i = 0; i < m; ++i) {
    auto t = clock();
    auto in = generate_input(n, k);
    auto t2 = clock();
    std::cout << double(t2 - t) / CLOCKS_PER_SEC << " Begin " << i << " ";
    std::cout << Solve(in) << " solve in " << double(clock() - t2) / CLOCKS_PER_SEC << "\n";
  }
}

*/

int main() {
  std::ios_base::sync_with_stdio(false);
  run();
  // test();
  return 0;
}
