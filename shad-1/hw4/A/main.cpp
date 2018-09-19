#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <algorithm>

struct Vertex {
  enum Color { W, B };
  Color color = Color::W;
  int component_index;
  int component_size = 0;
  std::unordered_set<int> outgoing_edges;
  std::unordered_set<int> incoming_edges;
};

typedef std::vector<Vertex> Graph;

void ColorWhite(Graph &graph) {
  for (auto &vertex : graph) {
    vertex.color = Vertex::W;
  }
}

void ForwardDFS(Vertex &vertex, Graph &graph, std::stack<Vertex *> &finished_vertices) {
  vertex.color = Vertex::B;
  for (auto neighbor : vertex.outgoing_edges) {
    if (graph[neighbor].color == Vertex::W) {
      ForwardDFS(graph[neighbor], graph, finished_vertices);
    }
  }
  finished_vertices.push(&vertex);
}

void BackwardDFS(Vertex &vertex, Graph &graph, int connectivity_index) {
  vertex.color = Vertex::B;
  for (auto neighbor : vertex.incoming_edges) {
    if (graph[neighbor].color == Vertex::W) {
      BackwardDFS(graph[neighbor], graph, connectivity_index);
    }
  }
  vertex.component_index = connectivity_index;
}

void MarkStrongConnectivity(Graph &graph) {
  std::stack<Vertex *> finished_vertices;
  for (auto &vertex : graph) {
    if (vertex.color == Vertex::W) {
      ForwardDFS(vertex, graph, finished_vertices);
    }
  }
  ColorWhite(graph);
  int connectivity_index = 0;
  while (!finished_vertices.empty()) {
    if (finished_vertices.top()->color == Vertex::W) {
      BackwardDFS(*finished_vertices.top(), graph, connectivity_index++);
    }
    finished_vertices.pop();
  }
}

Graph GetCondensationGraph(Graph &graph) {
  int size = 0;
  for (const auto &vertex : graph) {
    if (size < vertex.component_index) {
      size = vertex.component_index;
    }
  }
  Graph result(static_cast<size_t>(size + 1));
  for (const auto &vertex : graph) {
    ++result[vertex.component_index].component_size;
    for (const auto &neighbor : vertex.outgoing_edges) {
      if (vertex.component_index != graph[neighbor].component_index) {
        result[vertex.component_index].outgoing_edges.insert(graph[neighbor].component_index);
        result[graph[neighbor].component_index].incoming_edges.insert(vertex.component_index);
      }
    }
  }
  return result;
}

Graph ReadGraph() {
  int sizeV, sizeE;
  std::cin >> sizeV >> sizeE;
  Graph graph(sizeV);
  int first, second, res;
  for (int counter = 0; counter < sizeE; ++counter) {
    std::cin >> first >> second >> res;
    if (res == 3) {
      continue;
    }
    if (res == 2) {
      std::swap(first, second);
    }
    --first;
    --second;
    graph[first].outgoing_edges.insert(second);
    graph[second].incoming_edges.insert(first);
  }
  return graph;
}

void Solve(Graph &graph) {
  MarkStrongConnectivity(graph);
  Graph condensation = GetCondensationGraph(graph);
  int result = 0;
  for (const auto &vertex : condensation) {
    if (vertex.incoming_edges.empty()) {
      result = std::max(result, static_cast<int>(graph.size()) - vertex.component_size + 1);
    }
  }
  std::cout << result;
}

int main() {
  Graph graph = ReadGraph();
  Solve(graph);
  return 0;
}
