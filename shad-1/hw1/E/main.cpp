#include <iostream>
#include <vector>
#include <algorithm>

struct Diamond {
  uint64_t cost;
  uint64_t weight;
};

struct Sequence {
  uint64_t bit_mask;
  uint64_t size;
  int64_t cost;
  int64_t weight;
  bool operator<(const Sequence &other) const {
    return weight < other.weight;
  }
};

class SegmentTree {
 public:
  template<class Iter>
  void Initialize(Iter begin, Iter end) {
    table.resize((end - begin) * 2);
    for (int i = 0; i < end - begin; ++i) {
      table[i + end - begin] = {begin[i], i, i + 1};
    }
    for (int i = table.size() / 2 - 1; i > 0; --i) {
      if (table[2 * i].value.cost < table[2 * i + 1].value.cost) {
        table[i] = {table[2 * i + 1].value, table[2 * i].begin, table[2 * i + 1].end};
      } else {
        table[i] = {table[2 * i].value, table[2 * i].begin, table[2 * i + 1].end};
      }
    }
  }

  Sequence Max(int begin, int end, int id = 1) {
    if (begin <= table[id].begin && table[id].end <= end) {
      return table[id].value;
    } else if (end <= table[id].begin || table[id].end <= begin) {
      return {0, 0, 0};
    } else {
      return std::max(Max(begin, end, 2 * id), Max(begin, end, 2 * id + 1),
                      [](const Sequence &left, const Sequence &right) {
                        return left.cost < right.cost;
                      });
    }
  }

 private:
  struct Segment {
    Sequence value;
    int begin;
    int end;
  };
  std::vector<Segment> table;
};

Sequence Join(const Sequence &first, const Sequence &second) {
  return {(second.bit_mask << first.size) + first.bit_mask, first.size + second.size,
          first.cost + second.cost, first.weight + second.weight};
}

void ReadInput(std::vector<Diamond> &result, int64_t &left, int64_t &right) {
  size_t size;
  std::cin >> size >> left >> right;
  result.resize(size);
  for (auto &diamond : result) {
    std::cin >> diamond.weight >> diamond.cost;
  }
}

void PrintAnswer(const Sequence &sequence) {
  int counter = 0;
  for (uint64_t index = 0; static_cast<bool>(sequence.bit_mask >> index); ++index) {
    counter += (sequence.bit_mask >> index) & 1;
  }
  std::cout << counter << "\n";
  for (uint64_t index = 0; static_cast<bool>(sequence.bit_mask >> index); ++index) {
    if (static_cast<bool>((sequence.bit_mask >> index) & 1)) {
      std::cout << index + 1 << " ";
    }
  }
  std::cout << "\n";
}

std::vector<Sequence> MakeSequences(const std::vector<Diamond> &diamonds) {
  std::vector<Sequence> result;
  for (uint64_t bit_mask = 0; !static_cast<bool>(bit_mask >> diamonds.size()); ++bit_mask) {
    int64_t cost = 0;
    int64_t weight = 0;
    for (uint64_t index = 0; index < diamonds.size(); ++index) {
      if (static_cast<bool>((bit_mask >> index) & 1)) {
        cost += diamonds[index].cost;
        weight += diamonds[index].weight;
      }
    }
    Sequence seq = Sequence{bit_mask, diamonds.size(), cost, weight};
    result.push_back(seq);
  }
  return result;
}

Sequence Solve(const std::vector<Diamond> &diamonds, int64_t left, int64_t right) {
  std::vector<Sequence> first = MakeSequences(
      std::vector<Diamond>{diamonds.begin(), diamonds.begin() + diamonds.size() / 2});
  std::vector<Sequence> second = MakeSequences(
      std::vector<Diamond>{diamonds.begin() + diamonds.size() / 2, diamonds.end()});
  std::sort(second.begin(), second.end());
  SegmentTree segment_tree;
  segment_tree.Initialize(second.begin(), second.end());
  Sequence best{0, 0, 0, 0};
  for (const auto &first_sequence : first) {
    int begin = static_cast<int>(
        std::lower_bound(second.begin(), second.end(),
                         Sequence{0, 0, 0, left - first_sequence.weight}) - second.begin());
    int end = static_cast<int>(
        std::upper_bound(second.begin(), second.end(),
                         Sequence{0, 0, 0, right - first_sequence.weight}) - second.begin());
    Sequence best_second = segment_tree.Max(begin, end);
    if (first_sequence.cost + best_second.cost > best.cost &&
        first_sequence.weight + best_second.weight >= left &&
        first_sequence.weight + best_second.weight <= right) {
      best = Join(first_sequence, best_second);
    };
  };
  return best;
}

/*

void GenerateInput(int size, std::vector<Diamond> &result, uint64_t &left, uint64_t &right) {
  result.resize(size);
  for(int i = 0; i < size; ++i) {
    result[i].weight = 1 + random() % 10;
    result[i].cost = 1 + random() % 10;
  }
  left = random()%(5 * size);
  right = random()%(5 * size);
  if (right < left) {
    std::swap(right, left);
  }
}

void PrintSum(const std::vector<Diamond> &input) {
  uint64_t cost = 0;
  uint64_t weight = 0;
  for(int i = 0; i < input.size(); ++i) {
    cost += input[i].cost;
    weight += input[i].weight;
  }
  std::cout << weight << " " << cost << "\n";
}

void PrintInput(const std::vector<Diamond> &input, uint64_t &left, uint64_t &right) {
  std::cout << input.size() << " " << left << " " << right << "\n";
  for(int i = 0; i < input.size(); ++i) {
    std::cout << input[i].weight << " " << input[i].cost << "\n";
  }
}


Sequence Test(const std::vector<Diamond> &diamonds, uint64_t left, uint64_t right) {
  std::vector<Sequence> sequences = MakeSequences(diamonds);
  Sequence best = {0, 0, 0, 0};
  for (int index = 1; index < static_cast<int>(sequences.size()); ++index) {
    if ((sequences[index].cost > best.cost) &&
        sequences[index].weight >= left &&
        sequences[index].weight <= right) {
      best = sequences[index];
    }
  }
  return best;
}

void test() {
  srand(time(0));
  for(int i = 0; i < 1; ++i) {
    std::vector<Diamond> input;
    uint64_t left, right;
    GenerateInput(26, input, left, right);
    Sequence answer = Solve(input, left, right);
    Sequence correct = Test(input, left, right);
    if (answer.cost < correct.cost) {
      std::cout << "Input:\n";
      PrintInput(input, left, right);
      std::cout << "Answer\n";
      PrintAnswer(answer);
      std::cout << "Correct\n";
      PrintAnswer(correct);
      std::cout << "\n\n";
    }
  }
};

*/

void solve() {
  std::vector<Diamond> input;
  int64_t left, right;
  ReadInput(input, left, right);
  Sequence answer = Solve(input, left, right);
  PrintAnswer(answer);
}

int main() {
  solve();
  return 0;
}
