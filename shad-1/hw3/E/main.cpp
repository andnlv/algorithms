#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

template<class T, class Compare = std::less<>>
class Heap {
 public:
  T Top() const;
  bool Pop(T &element, size_t position = 0);
  bool Pop(size_t position = 0);
  size_t Push(const T &element);
  bool Empty() const;
  size_t Size() const;
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
size_t Heap<T, Compare>::Size() const {
  return storage_.size();
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
bool Heap<T, Compare>::Pop(size_t position) {
  if (storage_.size() <= position) {
    return false;
  }
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

struct Input {
  std::vector<int> numbers;
  std::queue<char> commands;
  int key;
};

struct IntForHeap {
  int value;
  bool in_min_heap;
  size_t heap_id;
};

namespace std {
template<>
void swap(IntForHeap *&first,
          IntForHeap *&second) noexcept {
  auto tmp = first;
  first = second;
  second = tmp;
  swap(first->heap_id, second->heap_id);
}

} // namespace std

class CmpMin {
 public:
  bool operator()(const IntForHeap *left, const IntForHeap *right) const {
    return left->value < right->value;
  }
};

class CmpMax {
 public:
  bool operator()(const IntForHeap *left, const IntForHeap *right) const {
    return left->value > right->value;
  }
};

Input ReadInput() {
  Input input;
  int commands_count, numbers_count;
  std::cin >> numbers_count >> commands_count >> input.key;
  input.numbers.resize(size_t(numbers_count));
  for (int i = 0; i < numbers_count; ++i) {
    std::cin >> input.numbers[i];
  }
  for (int i = 0; i < commands_count; ++i) {
    char buff;
    std::cin >> buff;
    input.commands.push(buff);
  }
  return input;
}

std::vector<int> Solve(Input input) {
  int right = 0;
  Heap<IntForHeap *, CmpMin> min_heap;
  Heap<IntForHeap *, CmpMax> max_heap;
  std::list<IntForHeap> array;
  std::vector<int> result;
  if (max_heap.Size() + 1 < static_cast<size_t>(input.key)) {
    array.push_back({input.numbers[0], false, max_heap.Size()});
    max_heap.Push(&array.back());
  } else {
    array.push_back({input.numbers[0], true, min_heap.Size()});
    min_heap.Push(&array.back());
  }
  while (!input.commands.empty()) {
    if (input.commands.front() == 'R') {
      ++right;
      if (max_heap.Size() + 1 < static_cast<size_t>(input.key)) {
        array.push_front({input.numbers[right], false, max_heap.Size()});
        max_heap.Push(&array.front());
      } else {
        if (!max_heap.Empty() && max_heap.Top()->value > input.numbers[right]) {
          IntForHeap* exchange_buffer;
          max_heap.Pop(exchange_buffer);
          exchange_buffer->in_min_heap = true;
          exchange_buffer->heap_id = min_heap.Size();
          min_heap.Push(exchange_buffer);

          array.push_front({input.numbers[right], false, max_heap.Size()});
          max_heap.Push(&array.front());
        } else {
          array.push_front({input.numbers[right], true, min_heap.Size()});
          min_heap.Push(&array.front());
        }
      }
    } else {
      if (array.back().in_min_heap) {
        min_heap.Pop(array.back().heap_id);
      } else {
        max_heap.Pop(array.back().heap_id);
        IntForHeap* exchange_buffer;
        if (min_heap.Pop(exchange_buffer)) {
          exchange_buffer->in_min_heap = false;
          exchange_buffer->heap_id = max_heap.Size();
          max_heap.Push(exchange_buffer);
        }
      }
      array.pop_back();
    }
    if (!min_heap.Empty()) {
      result.push_back(min_heap.Top()->value);
    } else {
      result.push_back(-1);
    }
    input.commands.pop();
  }
  return result;
}

void PrintAnswer(std::vector<int> answer, std::ostream &out = std::cout) {
  for (auto a : answer) {
    out << a << "\n";
  }
}

void run() {
  PrintAnswer(Solve(ReadInput()));
}

int main() {
  std::cin.sync_with_stdio(false);
  run();
  return 0;
}
