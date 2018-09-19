#include <iostream>
#include <vector>
#include <algorithm>

struct Coin {
  int t_;
  int x_;
};

struct Segment {
  Coin right, left;
  int time_r, time_l;
};

std::vector<Coin> read_input(std::istream &in = std::cin) {
  int size;
  in >> size;
  std::vector<Coin> result(size);
  for (int i = 0; i < size; ++i) {
    in >> result[i].x_ >> result[i].t_;
  }
  return result;
}

void prepare_coins(std::vector<Coin> &coins) {
  std::sort(coins.begin(), coins.end(), [](Coin lhc, Coin rhc) {
    return lhc.t_ < rhc.t_;
  });
  std::vector<Coin> new_coins;
  int left, right;
  left = right = coins[0].x_;
  new_coins.push_back(coins[0]);
  for (int i = 1; i < static_cast<int>(coins.size()); ++i) {
    if (coins[i].x_ < left) {
      left = coins[i].x_;
      new_coins.push_back(coins[i]);
    } else if (coins[i].x_ > right) {
      right = coins[i].x_;
      new_coins.push_back(coins[i]);
    }
  }
  coins = std::move(new_coins);
}

int solve(std::vector<Coin> coins) {
  if (coins.size() == 1) {
    return 0;
  }
  prepare_coins(coins);
  std::vector<Segment> segments(coins.size());
  Segment new_segment;
  segments[0].right = segments[0].left = coins[0];
  segments[0].time_r = segments[0].time_l = 0;
  for (int it = 1; it < static_cast<int>(coins.size()); ++it) {
    if (segments[it - 1].right.x_ < coins[it].x_) {
      new_segment.right = coins[it];
      new_segment.left = segments[it - 1].left;

      new_segment.time_r = segments[it - 1].time_r +
          (new_segment.right.x_ - segments[it - 1].right.x_);
      Segment current_segment = {coins[it], coins[it], 0, 0};
      for (int j = 0; j != it; ++j) {
        if (coins[j].x_ < current_segment.left.x_ &&
            coins[j].t_ < current_segment.time_r +
                2 * coins[it].x_ - current_segment.right.x_ - coins[j].x_) {
          current_segment = segments[j];
        }
      }
      new_segment.time_l = current_segment.time_r +
          2 * coins[it].x_ - current_segment.right.x_ - new_segment.left.x_;
    }
    if (segments[it - 1].left.x_ > coins[it].x_) {
      new_segment.left = coins[it];
      new_segment.right = segments[it - 1].right;

      new_segment.time_l = segments[it - 1].time_l -
          (new_segment.left.x_ - segments[it - 1].left.x_);
      Segment current_segment = {coins[it], coins[it], 0, 0};
      for (int j = 0; j != it; ++j) {
        if (coins[j].x_ > current_segment.right.x_ &&
            coins[j].t_ < current_segment.time_l -
                2 * coins[it].x_ + current_segment.left.x_ + coins[j].x_) {
          current_segment = segments[j];
        }
      }
      new_segment.time_r = current_segment.time_l -
          2 * coins[it].x_ + current_segment.left.x_ + new_segment.right.x_;
    }
    if (new_segment.time_l > new_segment.left.t_ &&
        new_segment.time_r > new_segment.right.t_) {
      return -1;
    }
    if (new_segment.time_r > new_segment.right.t_) {
      new_segment.right = new_segment.left;
      new_segment.time_r = new_segment.time_l;
    }
    if (new_segment.time_l > new_segment.left.t_) {
      new_segment.left = new_segment.right;
      new_segment.time_l = new_segment.time_r;
    }
    segments[it] = new_segment;
  }
  return std::min(segments.back().time_r, segments.back().time_l);
}

/*
std::stringstream generate_input(int n, int k) {
  std::stringstream buf;
  buf << n <<"\n";
  std::random_device generator;
  std::uniform_int_distribution<int64_t> random(1, k);
  for (int i = 0; i < n; ++i) {
    buf << random(generator) << " " << random(generator) << "\n";
  }
  return buf;
}

int stupied_solve(std::vector<Coin> coins) {
  int min_time = INT32_MAX;
  auto cmp = [](Coin lhc, Coin rhc) {
    return lhc.x_ < rhc.x_;
  };
  std::sort(coins.begin(), coins.end(), cmp);
  do {
    int time = 0;
    bool flag = true;
    for(int i = 1; i < coins.size() && flag; ++i) {
      time += std::abs(coins[i].x_ - coins[i - 1].x_);
      if(time > coins[i].t_) {
        flag = false;
      }
    }
    if(flag && time < min_time) {
      min_time = time;
    }
  } while (std::next_permutation(coins.begin(), coins.end(), cmp));
  if(min_time == INT32_MAX) {
    return -1;
  }
  return min_time;
}

void test() {
  std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
  std::cout.precision(6);
  int n, k, t;
  std::cin >> n >> k >> t;
  for(int i = 0; i < t; ++i) {
    auto in = generate_input(n, k);
    std::string wrong_in = in.str();
    auto input = read_input(in);
    int answer = solve(input);
    int correct_answer = stupied_solve(input);
    if(answer != correct_answer) {
      std::cout << "WA\n";
      std::cout << wrong_in << "\n";
      std::cout << "answer  = " << answer << "\n";
      std::cout << "correct = " << correct_answer << "\n\n";
    }
  }
}
*/

void print_answer(int answer) {
  if (answer == -1) {
    std::cout << "No solution\n";
    return;
  }
  std::cout << answer << "\n";
}

void run() {
  print_answer(solve(read_input()));
}

int main() {
  run();
  // test();
  return 0;
}
