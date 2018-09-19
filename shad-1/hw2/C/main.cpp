#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

class point {
 public:
  double x_;
  double y_;
  std::pair<double, double> get_crossings(double radius) const {
    double srt = sqrt(radius * radius - y_ * y_);
    return {x_ - srt, x_ + srt};
  };
  double distance(const point &other) const {
    return sqrt((other.x_ - x_) * (other.x_ - x_) +
        (other.y_ - y_) * (other.y_ - y_));
  }
};

std::pair<int, std::vector<point>> read_input(std::istream &in = std::cin) {
  int points_number, reqired_number;
  in >> points_number >> reqired_number;
  std::vector<point> points(points_number);
  for (int i = 0; i < points_number; ++i) {
    in >> points[i].x_ >> points[i].y_;
  }
  return {reqired_number, points};
};

int count_crossings(const std::vector<point> &points, double radius) {
  std::vector<std::pair<double, int>> crossings;
  for (auto &point : points) {
    if (radius > std::abs(point.y_)) {
      auto cur_cros = point.get_crossings(radius);
      crossings.push_back({cur_cros.first, 1});
      crossings.push_back({cur_cros.second, -1});
    }
  }
  std::sort(crossings.begin(), crossings.end(), [](auto left, auto right) {
              return left.first < right.first;
            }
  );
  int counter = 0;
  int max_counter = 0;
  for (auto &cross : crossings) {
    counter += cross.second;
    max_counter = std::max(max_counter, counter);
  }
  return max_counter;
}

double bin_search(int reqired_number, const std::vector<point> &points) {
  double min = 0;
  double max = 2000;
  double eps = 0.001;
  while (max - min > eps) {
    if (count_crossings(points, (max + min) / 2) >= reqired_number) {
      max = (max + min) / 2;
    } else {
      min = (max + min) / 2;
    }
  }
  return (max + min) / 2;
}

double solve(std::pair<int, std::vector<point>> input) {
  std::sort(input.second.begin(), input.second.end(), [](auto x, auto y) {
    return x.x_ < y.x_;
  });
  return bin_search(input.first, input.second);
}

void run() {
  std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
  std::cout.precision(6);
  std::cout << solve(read_input());
}

/*
std::stringstream generate_input(int n, int k, int m) {
  std::stringstream buf;
  buf << n << " " << k <<"\n";
  std::random_device generator;
  std::uniform_int_distribution<int64_t> random(-m, m);
  for (int i = 0; i < n; ++i) {
    buf << random(generator) << " " << random(generator) << "\n";
  }
  return buf;
}

bool chech_answer(int k, std::vector<point> &points, double answer, int m) {
  double eps = 0.001;
  for(double x0 = -m; x0 < m; x0 += eps) {
    int counter = 0;
    for(auto& point : points) {
      counter += ((point.distance({x0, 0})) < answer + eps);
    }
    if(counter >= k) {
      return true;
    }
  }
  return false;
}

void test() {
  std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
  std::cout.precision(6);
  int n, k, m, t;
  std::cin >> n >> k >> m >> t;
  for(int i = 0; i < t; ++i) {
    auto in = generate_input(n, k, m);
    std::string wrong_in = in.str();
    auto input = read_input(in);
    double answer = solve(input);
    if(!chech_answer(input.first, input.second, answer, m)) {
      std::cout << "WRONG ANSWER!!\n";
      std::cout << wrong_in << "\n";
    }
  }
}
*/

int main() {
  run();
  // test();
  return 0;
}
