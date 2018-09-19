#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>
#include <fstream>
#include <cassert>
#include <random>
#include <memory>
#include <chrono>
#include <ctime>
#include <utility>
#include <functional>

template<class T, class Compare = std::less<>>
class Heap {
 public:
  T Top() const;
  T Pop(size_t position = 0);
  size_t Push(const T &element);
  bool Empty() const;
  size_t Size() const;
 public:
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
T Heap<T, Compare>::Pop(size_t position) {
  assert(position < storage_.size());
  std::swap(storage_[position], storage_.back());
  T result = storage_.back();
  storage_.pop_back();
  sift_down_(position);
  sift_up_(position);
  return result;
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

struct Vertex {
  std::vector<Vertex *> neighbors;
  enum Color { W, B };
  Color color;
  int layer;
  int key;
  int id;
};

typedef std::vector<std::shared_ptr<Vertex>> Graph;

std::array<Graph, 2> ReadInput(std::istream &in = std::cin) {
  size_t size;
  in >> size;
  std::array<Graph, 2> graphs;
  for (auto &graph : graphs) {
    graph.resize(size);
    for (int i = 0; i < size; ++i) {
      graph[i] = std::make_shared<Vertex>();
      graph[i]->id = i + 1;
    }
    for (int i = 0; i + 1 < graph.size(); ++i) {
      int vertex_first, vertex_second;
      in >> vertex_first >> vertex_second;
      --vertex_first;
      --vertex_second;
      graph[vertex_first]->neighbors.push_back(&*graph[vertex_second]);
      graph[vertex_second]->neighbors.push_back(&*graph[vertex_first]);
    }
  }
  return graphs;
}

void ColorWhite(Graph &graph) {
  for (auto &vertex :graph) {
    vertex->color = Vertex::W;
  }
}

std::vector<Vertex *> FindLongestChain(Vertex *vertex) {
  std::vector<Vertex *> longest_chain;
  std::vector<Vertex *> chain;
  vertex->color = Vertex::B;
  for (auto neighbor : vertex->neighbors) {
    if (neighbor->color == Vertex::W) {
      chain = FindLongestChain(neighbor);
    }
    if (chain.size() > longest_chain.size()) {
      std::swap(longest_chain, chain);
    }
  }
  longest_chain.push_back(vertex);
  return longest_chain;
}

std::pair<Vertex *, Vertex *> FindRoot(Graph &graph) {
  std::vector<Vertex *> chain = FindLongestChain(&*graph.front());
  ColorWhite(graph);
  chain = FindLongestChain(chain[0]);
  ColorWhite(graph);
  if (chain.size() % 2 == 1) {
    return {chain[chain.size() / 2], chain[chain.size() / 2]};
  }
  return {chain[chain.size() / 2 - 1], chain[chain.size() / 2]};
}

class CmpWithKeys {
 public:
  bool operator()(Vertex *&first, Vertex *&second) {
    if (first->layer != second->layer)
      return first->layer > second->layer;
    if (first->neighbors.size() != second->neighbors.size()) {
      return first->neighbors.size() < second->neighbors.size();
    }
    for (int i = 0; i < first->neighbors.size(); ++i) {
      if (first->neighbors[i]->key != second->neighbors[i]->key) {
        return first->neighbors[i]->key < second->neighbors[i]->key;
      }
    }
    return false;
  }
};

class Cmp {
 public:
  bool operator()(Vertex *&first, Vertex *&second) {
    if (first->layer != second->layer)
      return first->layer > second->layer;
    if (first->neighbors.size() != second->neighbors.size()) {
      return first->neighbors.size() < second->neighbors.size();
    }
    for (int i = 0; i < first->neighbors.size(); ++i) {
      if (first->neighbors[i]->key != second->neighbors[i]->key) {
        return first->neighbors[i]->key < second->neighbors[i]->key;
      }
    }
    return false;
  }
};

bool vertex_eq(Vertex *&first, Vertex *&second) {
  if (first->layer != second->layer)
    return false;
  if (first->neighbors.size() != second->neighbors.size()) {
    return false;
  }
  for (int i = 0; i < first->neighbors.size(); ++i) {
    if (first->neighbors[i]->key != second->neighbors[i]->key) {
      return false;
    }
  }
  return true;
}

std::vector<int> FindIsomorphism(std::array<Graph, 2> &graphs, std::array<Vertex *, 2> roots) {

  // double t = clock();
  std::array<Heap<Vertex *, Cmp>, 2> heaps;
  // BFS
  for (int ii = 0; ii < 2; ++ii) {
    std::queue<Vertex *> bfs_queue;
    Vertex *vertex;
    roots[ii]->layer = 0;

    roots[ii]->color = Vertex::B;
    bfs_queue.push(roots[ii]);
    while (!bfs_queue.empty()) {
      vertex = bfs_queue.front();
      bfs_queue.pop();
      heaps[ii].Push(vertex);
      for (auto neighbor : vertex->neighbors) {
        if (neighbor->color == Vertex::W) {
          neighbor->layer = vertex->layer + 2;
          neighbor->color = Vertex::B;
          bfs_queue.push(neighbor);
        }
      }
    }
  }

  // std::cout << "bfs " << (clock() - t)/CLOCKS_PER_SEC << std::endl;
  // t = clock();
  // Setting keys
  for (int ij = 0; ij < 2; ++ij) {
    Vertex *prev_vertex = heaps[ij].Pop();
    int current_layer = prev_vertex->layer - 1;
    prev_vertex->key = 0;
    while (!heaps[ij].Empty()) {
      if (current_layer > heaps[ij].Top()->layer) {
        current_layer -= 2;
        while (current_layer > heaps[ij].Top()->layer) {
          Vertex *vertex = heaps[ij].Pop();
          vertex->layer -= 1;
          std::sort(vertex->neighbors.begin(), vertex->neighbors.end(),
                    [](Vertex *first, Vertex *second) {
            return first->key < second->key;
          });
          heaps[ij].Push(vertex);
        }
      }
      Vertex *curr_vertex = heaps[ij].Pop();
      if (vertex_eq(curr_vertex, prev_vertex)) {
        curr_vertex->key = prev_vertex->key;
      } else {
        curr_vertex->key = prev_vertex->key + 1;
      }
    }
  }
  // std::cout << "setting keys " << (clock() - t)/CLOCKS_PER_SEC << std::endl;
  // t = clock();
  ColorWhite(graphs[0]);
  ColorWhite(graphs[1]);
  std::vector<std::array<Vertex *, 2>> bijection;
  std::array<Vertex *, 2> vertices;
  std::queue<std::array<Vertex *, 2>> bfs_queues;

  for (int i = 0; i < 2; ++i) {
    roots[i]->color = Vertex::B;
  }
  bfs_queues.push({roots[0], roots[1]});

  while (!bfs_queues.empty()) {
    vertices = bfs_queues.front();
    bfs_queues.pop();
    if (vertex_eq(vertices[0], vertices[1])) {
      bijection.push_back({vertices[0], vertices[1]});
    } else {
      return std::vector<int>();
    }
    for (int j = 0; j < vertices[0]->neighbors.size(); ++j) {
      if (vertices[0]->neighbors[j]->color == Vertex::W) {
        vertices[0]->neighbors[j]->color = Vertex::B;
        bfs_queues.push({vertices[0]->neighbors[j], vertices[1]->neighbors[j]});
      }
    }
  }

  std::vector<int> result(bijection.size());
  for (const auto &pair : bijection) {
    result[pair[0]->id - 1] = pair[1]->id - 1;
  }
  // std::cout << "building bijection " << (clock() - t)/CLOCKS_PER_SEC << std::endl;
  return result;
}

std::vector<int> Solve(std::array<Graph, 2> &graphs) {
  std::array<std::pair<Vertex *, Vertex *>, 2> roots;
  double time = clock();
  for (int i = 0; i < 2; ++i) {
    roots[i] = FindRoot(graphs[i]);
  }
  if (((roots[0].first == roots[0].second) != (roots[1].first == roots[1].second)) ||
      graphs[0].size() != graphs[1].size() ||
      (roots[0].first->neighbors.size() != roots[1].first->neighbors.size() &&
          roots[0].first->neighbors.size() != roots[1].second->neighbors.size())) {
    return std::vector<int>();
  }

  std::vector<int> first_result = FindIsomorphism(graphs, {roots[0].first, roots[1].first});
  if (first_result.size() == 0 && roots[1].first != roots[1].second) {
    ColorWhite(graphs[0]);
    ColorWhite(graphs[1]);
    return FindIsomorphism(graphs, {roots[0].first, roots[1].second});
  }
  return first_result;
}

void PrintAnswer(const std::vector<int> &answer, std::ostream &out = std::cout) {
  if (answer.empty()) {
    out << -1 << "\n";
  }
  for (const auto &i : answer) {
    out << i + 1 << "\n";
  }
}

void run() {
  auto input = ReadInput();
  auto answer = Solve(input);
  PrintAnswer(answer);
}

/*
void generate_test(int n, std::ostream &out) {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::srand(seed);
  std::mt19937 generator(seed);
  std::vector<int> v(n);

  out << n << "\n";
  for(int i = 1; i < n; ++i) {
    std::uniform_int_distribution<int> rand_int(0, i - 1);
    v[i] = rand_int(generator);
    out << i + 1 << " " << v[i] + 1 << "\n";
  }
  std::vector<int> perm(n);
  std::iota(perm.begin(), perm.end(), 0);
  std::random_shuffle(perm.begin(), perm.end());

  for(int i = 1; i < n; ++i) {
    out << perm[i] + 1 << " " << perm[v[i]] + 1 << "\n";
  }
}

void hand_test() {
  std::ifstream fin;
  fin.open("input.txt");
  auto input = ReadInput(fin);
  auto answer = Solve(input);
  PrintAnswer(answer);
}

void test() {
  int n = 8;
  int t = 1;
  std::cin >> n >> t;
  std::ofstream fout;
  std::ifstream fin;
  for(int i = 0; i < t; ++i) {
    fout.open("input.txt");
    generate_test(n, fout);
    fout.close();

    fin.open("input.txt");
    auto input = ReadInput(fin);
    double time = clock();
    auto answer = Solve(input);
    std::cout << (clock() - time)/CLOCKS_PER_SEC << std::endl;
    fin.close();
    if(answer.empty()){
      std::cout << "ERROR\n";
      exit(1);
    }
  }
}
*/

int main() {
  std::cin.sync_with_stdio(false);
  run();
  // test();
  return 0;
}
