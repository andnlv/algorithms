#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

struct Vertex : public std::unordered_map<int, int> {
  int in;
  int up = std::numeric_limits<int>::max();
  enum Color { W, G, B };
  Color color = Color::W;
};

typedef std::vector<Vertex> Graph;

int GetTime() {
  static int time = 0;
  return ++time;
}

Graph ReadGraph(std::istream &in = std::cin) {
  int Vsize, Esize;
  in >> Vsize;
  in >> Esize;
  Graph graph(Vsize);
  for (int i = 0; i < Esize; ++i) {
    int from, to, cost;
    in >> from >> to >> cost;
    --to;
    --from;
    graph[from][to] = cost;
    graph[to][from] = cost;
  }
  return graph;
}

void dfs(int vertex, int from, Graph &graph) {
  graph[vertex].color = Vertex::Color::G;
  graph[vertex].in = GetTime();
  for (auto neighbor : graph[vertex]) {
    if (graph[neighbor.first].color == Vertex::Color::W) {
      dfs(neighbor.first, vertex, graph);
    }
    if (neighbor.first != from) {
      graph[vertex].up = std::min(std::min(graph[vertex].up,
                                           graph[neighbor.first].in), graph[neighbor.first].up);
    }
  }
  graph[vertex].color = Vertex::Color::B;
}

void solve(Graph graph) {
  bool found = false;
  for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
    if (graph[i].color == Vertex::Color::W) {
      dfs(i, -1, graph);
    }
  }
  int result = std::numeric_limits<int>::max();
  for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
    for (auto j : graph[i]) {
      if (graph[i].in < graph[j.first].in) {
        if (graph[j.first].up >= graph[j.first].in) {
          if (j.second < result) {
            found = true;
            result = j.second;
          }
        }
      }
    }
  }
  std::cout << (found ? result : -1);
}

int main() {
  solve(ReadGraph());
  return 0;
}
