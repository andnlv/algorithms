#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

template<class T, class Compare = std::less<>>
class Heap {
 public:
  T Top() const;
  bool Pop(T &element, size_t position = 0);
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
size_t Heap<T, Compare>::Size() const {
  return storage_.size();
}

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

struct MemoryBlock {
  int begin;
  int size;
  size_t heap_id;
  bool free;
  MemoryBlock *next;
  MemoryBlock *prev;
};

namespace std {
template<>
void swap(std::shared_ptr<MemoryBlock> &first,
          std::shared_ptr<MemoryBlock> &second) noexcept {
  auto tmp = first;
  first = second;
  second = tmp;
  swap(first->heap_id, second->heap_id);
}

} // namespace std

class Cmp {
 public:
  bool operator()(const std::shared_ptr<MemoryBlock> &lhc,
                  const std::shared_ptr<MemoryBlock> &rhc) const {
    if (lhc->size != rhc->size) {
      return lhc->size > rhc->size;
    }
    return lhc->begin < rhc->begin;
  };
};

struct Input {
  int memory_size;
  std::vector<int> requests;
};

Input ReadInput(std::istream &in = std::cin) {
  int memory_size, requests_size;
  in >> memory_size >> requests_size;
  std::vector<int> requests(requests_size);
  for (auto &request : requests) {
    in >> request;
  }
  return {memory_size, requests};
}

std::vector<int> Solve(Input input) {
  Heap<std::shared_ptr<MemoryBlock>, Cmp> heap;
  std::vector<std::shared_ptr<MemoryBlock>> blocks;
  std::shared_ptr<MemoryBlock> block(std::make_shared<MemoryBlock>());
  std::vector<int> result;
  block->begin = 0;
  block->size = input.memory_size;
  block->heap_id = 0;
  block->free = true;
  block->prev = nullptr;
  block->next = nullptr;
  block->heap_id = 0;
  heap.Push(block);
  for (auto request : input.requests) {
    if (request > 0) {
      if (heap.Empty()) {
        blocks.push_back(nullptr);
        result.push_back(-2);
        continue;
      }
      if (heap.Top()->size > request) {
        std::shared_ptr<MemoryBlock> free_block;
        heap.Pop(free_block);
        std::shared_ptr<MemoryBlock> new_block(std::make_shared<MemoryBlock>());
        new_block->next = &*free_block;
        new_block->prev = free_block->prev;
        if (free_block->prev) {
          free_block->prev->next = &*new_block;
        }
        new_block->size = request;
        new_block->free = false;
        new_block->begin = free_block->begin;

        free_block->prev = &*new_block;
        free_block->begin += request;
        free_block->size -= request;

        free_block->heap_id = heap.Size();
        heap.Push(free_block);
        blocks.push_back(new_block);
        result.push_back(new_block->begin);
      } else if (heap.Top()->size == request) {
        std::shared_ptr<MemoryBlock> new_block;
        heap.Pop(new_block);
        new_block->free = false;
        blocks.push_back(new_block);
        result.push_back(new_block->begin);
      } else {
        blocks.push_back(nullptr);
        result.push_back(-2);
      }
    } else {
      request = -request - 1;
      blocks.push_back(nullptr);
      if (static_cast<size_t>(request) >= blocks.size() || blocks[request] == nullptr) {
        continue;
      }
      std::shared_ptr<MemoryBlock> current_block = blocks[request];
      current_block->free = true;
      if (current_block->next && current_block->next->free) {
        heap.Pop(block, current_block->next->heap_id);
        current_block->size += current_block->next->size;
        current_block->next = current_block->next->next;
        if (current_block->next) {
          current_block->next->prev = &*current_block;
        }
      }
      if (current_block->prev && current_block->prev->free) {
        heap.Pop(block, current_block->prev->heap_id);
        current_block->size += current_block->prev->size;
        current_block->begin = current_block->prev->begin;
        current_block->prev = current_block->prev->prev;
        if (current_block->prev) {
          current_block->prev->next = &*current_block;
        }
      }
      current_block->heap_id = heap.Size();
      heap.Push(current_block);
    }
  }
  return result;
}

void PrintAnswer(std::vector<int> answer, std::ostream &out = std::cout) {
  for (auto a : answer) {
    out << a + 1 << "\n";
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
