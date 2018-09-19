#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <utility>
#include <vector>

struct Player {
  int playerId;
  int64_t efficiency;
};

std::vector<Player> ReadInput(std::istream &in = std::cin);

template<class Iterator>
Iterator ChoosePivot(Iterator begin, Iterator end);

template<class Iterator, class Compare>
Iterator Partition(Iterator begin, Iterator end, Iterator pivot, Compare compare);

template<class Iterator, class Compare>
void Sort(Iterator begin, Iterator end, Compare compare = std::less<>());

std::vector<Player> GetPerfectTeam(std::vector<Player> players);

int64_t GetTotalEfficiency(const std::vector<Player> &players);

void PrintAnswer(std::vector<Player> answer, std::ostream &out = std::cout);

int main() {
  PrintAnswer(GetPerfectTeam(ReadInput()));
  return 0;
}

std::vector<Player> ReadInput(std::istream &in) {
  int size;
  std::vector<Player> players;
  in >> size;
  players.reserve(static_cast<size_t>(size));
  for (int i = 1; i <= size; ++i) {
    int efficiency;
    in >> efficiency;
    players.push_back({i, efficiency});
  }
  return players;
}

template<class Iterator>
Iterator ChoosePivot(Iterator begin, Iterator end) {
  static std::random_device generator;
  std::uniform_int_distribution<int> random(0, end - begin - 1);
  return begin + random(generator);
}

template<class Iterator, class Compare>
Iterator Partition(Iterator begin, Iterator end,
                   typename Iterator::value_type pivot, Compare compare) {
  Iterator right = begin;
  Iterator left = begin;

  // this flag is true if previously comparing equal elements we moved left iterator.
  // It is needed for a case, when there are a lot of elements equal to pivot.
  bool previously_moved_left = false;
  while (right < end) {
    if (!(compare(*right, pivot) || compare(pivot, *right))) {
      previously_moved_left = !previously_moved_left;
      if (previously_moved_left) {
        std::iter_swap(right, left);
        ++left;
      }
    } else if (compare(*right, pivot)) {
      std::iter_swap(right, left);
      ++left;
    }
    ++right;
  }
  return left;
}

template<class Iterator, class Compare>
void Sort(Iterator begin, Iterator end, Compare compare) {
  if (end - begin <= 1) {
    return;
  }
  auto pivot = ChoosePivot(begin, end);
  Iterator middle = Partition(begin, end, *pivot, compare);
  Sort(begin, middle, compare);
  Sort(middle, end, compare);
};

std::vector<Player> GetPerfectTeam(std::vector<Player> players) {
  if (players.size() <= 2) {
    return players;
  }
  Sort(players.begin(), players.end(),
       [](const Player &first, const Player &second) {
         return first.efficiency < second.efficiency;
       });

  struct Team {
    int64_t sum;
    std::vector<Player>::iterator left;
    std::vector<Player>::iterator right;
  };

  Team team{
      players.front().efficiency,
      players.begin(),
      players.begin() + 1
  };
  Team perfect_team = team;

  while (team.right <= players.end()) {
    if (team.right - team.left > 2 && (team.right - 1)->efficiency >
        team.left->efficiency + (team.left + 1)->efficiency) {
      team.sum -= team.left->efficiency;
      ++team.left;
      continue;
    }
    if (team.sum > perfect_team.sum) {
      perfect_team = team;
    }
    if (team.right < players.end()) {
      team.sum += team.right->efficiency;
    }
    ++team.right;
  }

  return {perfect_team.left, perfect_team.right};
}

int64_t GetTotalEfficiency(const std::vector<Player> &players) {
  int64_t result = 0;
  for (const auto &player : players) {
    result += player.efficiency;
  }
  return result;
}

void PrintAnswer(std::vector<Player> answer, std::ostream &out) {
  Sort(answer.begin(), answer.end(),
       [](const Player &first, const Player &second) {
         return first.playerId < second.playerId;
       });
  std::cout << GetTotalEfficiency(answer) << "\n";
  for (const auto &player: answer) {
    std::cout << player.playerId << " ";
  }
  std::cout << "\n";
}
