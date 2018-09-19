#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <utility>
#include <vector>

class Hash {
 public:
  void Initialize(std::random_device &generator);
  uint64_t operator()(int element) const;

 private:
  uint64_t a_, b_;
  static const uint64_t prime_ = 2000000011;
  static const int min_number_ = -1000000000;
};

class FixedSet {
 public:
  void Initialize(const std::vector<int> &input);
  bool Contains(int number) const;

 private:
  static bool CheckDistribution(const std::vector<int> &elements);
  static Hash GenerateHashFunction(const std::vector<int> &input,
                            std::random_device &generator,
                            const std::function<bool(const std::vector<int>&)> &predicate,
                                   size_t size);

  static std::vector<int> CountElementsDistribution(const std::vector<int> &elements,
                                                    const Hash &hash, size_t size);

  class Bucket {
   public:
    void Initialize(const std::vector<int> &numbers, std::random_device &generator);
    bool Contains(int number) const;

   private:
    static bool CheckDistribution(const std::vector<int> &elements);
    std::vector<std::pair<bool, int>> elements_;
    Hash hash_;
  };

  std::vector<Bucket> buckets_;
  Hash hash_;
  static const int init_factor_ = 4;
};

std::vector<int> ReadVector(std::istream &in = std::cin);

std::vector<bool> CheckInclusion(const std::vector<int> &input, const std::vector<int> &queries);

void PrintAnswer(std::vector<bool> &answers, std::ostream &out = std::cout);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto input = ReadVector();
  auto queries = ReadVector();
  auto answer = CheckInclusion(input, queries);
  PrintAnswer(answer);
  return 0;
}

uint64_t Hash::operator()(int element) const {
  return (a_ * static_cast<uint32_t>(element - min_number_) + b_) % prime_;
}

std::vector<int> FixedSet::CountElementsDistribution(const std::vector<int> &elements,
                                                     const Hash &hash, size_t size) {
  std::vector<int> result(size, 0);
  for (const auto &element : elements) {
    ++result[hash(element) % size];
  }
  return result;
}

bool FixedSet::CheckDistribution(const std::vector<int> &elements) {
  return std::inner_product(elements.begin(), elements.end(), elements.begin(), 0) <
      init_factor_* static_cast<int>(elements.size());
}

bool FixedSet::Bucket::CheckDistribution(const std::vector<int> &elements) {
  return *std::max_element(elements.begin(), elements.end()) <= 1;
}

Hash FixedSet::GenerateHashFunction(const std::vector<int> &input,
                                    std::random_device &generator,
                                    const std::function<bool(const std::vector<int>&)> &predicate,
                                    size_t size) {
  Hash hash;
  do {
    hash.Initialize(generator);
  } while (!predicate(CountElementsDistribution(input, hash, size)));
  return hash;
}

void Hash::Initialize(std::random_device &generator) {
  a_ = std::uniform_int_distribution<uint64_t>(1, prime_)(generator);
  b_ = std::uniform_int_distribution<uint64_t>(0, prime_)(generator);
}

void FixedSet::Initialize(const std::vector<int> &input) {
  static std::random_device generator;
  buckets_.resize(input.size());
  hash_ = GenerateHashFunction(input, generator, CheckDistribution, input.size());

  std::vector<std::vector<int>> table(input.size());
  for (auto number : input) {
    table[hash_(number) % table.size()].push_back(number);
  }
  for (int i = 0; i < static_cast<int>(buckets_.size()); ++i) {
    if (!table[i].empty()) {
      buckets_[i].Initialize(table[i], generator);
    }
  }
}

void FixedSet::Bucket::Initialize(const std::vector<int> &numbers,
                                  std::random_device &generator) {
  elements_.resize(numbers.size() * numbers.size(), {false, 0});
  hash_ = GenerateHashFunction(numbers, generator, CheckDistribution, elements_.size());
  for (auto number : numbers) {
    elements_[hash_(number) % elements_.size()] = {true, number};
  }
}

bool FixedSet::Contains(int number) const {
  return !buckets_.empty() && buckets_[hash_(number) % buckets_.size()].Contains(number);
}

bool FixedSet::Bucket::Contains(int number) const {
  return !elements_.empty() && elements_[hash_(number) % (elements_.size())] ==
      std::pair<bool, int>(true, number);
}


std::vector<int> ReadVector(std::istream &in) {
  size_t size;
  in >> size;
  std::vector<int> result(size);
  for (auto &number : result) {
    in >> number;
  }
  return result;
}

std::vector<bool> CheckInclusion(const std::vector<int> &input, const std::vector<int> &queries) {
  FixedSet set;
  set.Initialize(input);
  std::vector<bool> result;
  for (auto query : queries) {
    result.push_back(set.Contains(query));
  }
  return result;
}

void PrintAnswer(std::vector<bool> &answers, std::ostream &out) {
  for (auto answer : answers) {
    out << (answer ? "Yes" : "No") << "\n";
  }
}
