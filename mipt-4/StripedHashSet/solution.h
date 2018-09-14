#ifndef solution_hpp
#define solution_hpp

#include <algorithm>
#include <condition_variable>
#include <forward_list>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

template<typename T, class Hash = std::hash<T>>
class StripedHashSet {
 public:
  explicit StripedHashSet(const size_t concurrency_level,
                          const size_t growth_factor = 3,
                          const double load_factor = 0.75);
  bool Insert(const T &element);
  bool Remove(const T &element);
  bool Contains(const T &element);
  size_t Size();
 private:
  std::vector<std::forward_list<T>> table_;
  std::vector<std::mutex> mutex_;
  const size_t growth_factor_;
  const double max_load_factor_;
  std::atomic<size_t> size_;
  Hash hash_;
 private:
  void Rehash();
  double LoadFactor();
  size_t GetBucketIndex(const size_t hash_value);
  size_t GetStripeIndex(const size_t hash_value);
  bool ElementInBucket(const T &element, size_t index);
};

template<typename T, class Hash>
StripedHashSet<T, Hash>::StripedHashSet(const size_t concurrency_level,
                                        const size_t growth_factor,
                                        const double max_load_factor)
    : table_(concurrency_level),
      mutex_(concurrency_level),
      growth_factor_(growth_factor),
      max_load_factor_(max_load_factor),
      size_(0){};

template<typename T, class Hash>
bool StripedHashSet<T, Hash>::Insert(const T &element) {
  const size_t hash = hash_(element);
  std::unique_lock<std::mutex> lock(mutex_[GetStripeIndex(hash)]);
  if (ElementInBucket(element, GetBucketIndex(hash))) {
    return false;
  }
  table_[GetBucketIndex(hash)].push_front(element);
  ++size_;
  if (LoadFactor() > max_load_factor_) {
    lock.unlock();
    Rehash();
  }
  return true;
}

template<typename T, class Hash>
bool StripedHashSet<T, Hash>::Remove(const T &element) {
  const size_t hash = hash_(element);
  std::unique_lock<std::mutex> lock(mutex_[GetStripeIndex(hash)]);
  if (!ElementInBucket(element, GetBucketIndex(hash))) {
    return false;
  }
  --size_;
  table_[GetBucketIndex(hash)].remove(element);
  return true;
}

template<typename T, class Hash>
void StripedHashSet<T, Hash>::Rehash() {
  std::vector<std::unique_lock<std::mutex>> lock(mutex_.size());
  lock[0] = std::unique_lock<std::mutex>(mutex_[0]);
  if (LoadFactor() < max_load_factor_) {
    return;
  }
  for (size_t i = 1; i < mutex_.size(); ++i) {
    lock[i] = std::unique_lock<std::mutex>(mutex_[i]);
  }

  std::vector<std::forward_list<T>> new_vector(table_.size() * growth_factor_);
  for (size_t i = 0; i < table_.size(); ++i) {
    for (auto it = table_[i].begin(); it != table_[i].end(); ++it) {
      new_vector[hash_(*it) % new_vector.size()].push_front(std::move(*it));
    }
  }
  table_ = std::move(new_vector);
}

template<typename T, class Hash>
bool StripedHashSet<T, Hash>::Contains(const T &element) {
  size_t hash = hash_(element);
  std::unique_lock<std::mutex> lock(mutex_[GetStripeIndex(hash)]);
  return ElementInBucket(element, GetBucketIndex(hash));
}

template<typename T, class Hash>
size_t StripedHashSet<T, Hash>::Size() {
  return size_;
}

template<typename T, class Hash>
size_t StripedHashSet<T, Hash>::GetBucketIndex(const size_t hash_value) {
  return hash_value % table_.size();
}

template<typename T, class Hash>
size_t StripedHashSet<T, Hash>::GetStripeIndex(const size_t hash_value) {
  return hash_value % mutex_.size();
}

template<typename T, class Hash>
double StripedHashSet<T, Hash>::LoadFactor() {
  return double(size_) / table_.size();
}

template<typename T, class Hash>
bool StripedHashSet<T, Hash>::ElementInBucket(const T &element, size_t index) {
  return std::find(table_[index].begin(), table_[index].end(), element) != table_[index].end();
}

template<typename T> using ConcurrentSet = StripedHashSet<T>;

#endif
