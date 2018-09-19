//
// Created by andrey on 03.11.17.
//

#ifndef D_HEAP_H
#define D_HEAP_H

#include <iostream>
#include <vector>

template<class T, class Compare = std::less<>>
class Heap {
 public:
  T Top() const;
  bool Pop(T &element, size_t position = 0);
  size_t Push(const T &element);
  bool Empty() const;
 private:
  std::vector<T> storage_;
  size_t sift_down_(size_t position);
  size_t sift_up_(size_t position);
  Compare compare;
};

template<class T, class Compare>
bool Heap<T, Compare>::Empty() const {
  return storage_.empty();
}

template<class T, class Compare>
T Heap<T, Compare>::Top() const {
  return storage_.front();
}

template<class T, class Compare>
bool Heap<T, Compare>::Pop(T &element, size_t position) {
  if (storage_.size() <= position) {
    return false;
  }
  element = storage_[position];
  std::swap(storage_[position], storage_.back());
  storage_.pop_back();
  sift_down_(position);
  sift_up_(position);
  return true;
}

template<class T, class Compare>
size_t Heap<T, Compare>::Push(const T &element) {
  storage_.push_back(element);
  return sift_up_(storage_.size() - 1);
}

template<class T, class Compare>
size_t Heap<T, Compare>::sift_up_(size_t position) {
  while (position > 0 && compare(storage_[position], storage_[(position - 1) / 2])) {
    std::swap(storage_[position], storage_[(position - 1) / 2]);
    position = (position - 1) / 2;
  };
  return position;
}

template<class T, class Compare>
size_t Heap<T, Compare>::sift_down_(size_t position) {
  while ((position * 2 + 2 < storage_.size() &&
      compare(storage_[position * 2 + 2], storage_[position])) ||
      (position * 2 + 1 < storage_.size() &&
          compare(storage_[position * 2 + 1], storage_[position]))) {
    if (position * 2 + 2 < storage_.size() &&
        compare(storage_[position * 2 + 2], storage_[position * 2 + 1])) {
      std::swap(storage_[position], storage_[position * 2 + 2]);
      position = position * 2 + 2;
    } else {
      std::swap(storage_[position], storage_[position * 2 + 1]);
      position = position * 2 + 1;
    }
  }
  return position;
}


#endif //D_HEAP_H
