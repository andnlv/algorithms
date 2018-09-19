//
//  Graph.hpp
//  Floid
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <array>
#include <string>

#ifndef Graph_hpp
#define Graph_hpp
class GraphVertex;
class GraphEdge;

class GraphVertex{
public:
    std::vector<int> outgoingEdges; //исходящие рёбра
    std::vector<int> incomingEdges; //входящие рёбра
    int vertexId; //id  вершины
};

class GraphEdge{
public:
    int vertexTo;
    int vertexFrom;
};

class WEdge : public GraphEdge{ // weighted edge
public:
    int weight;
};

template <class E = GraphEdge, class V = GraphVertex>
class Graph{
public:
    Graph();
    Graph(const std::vector<std::vector<E>>& graph); // инициализация списком смежности
    int addVertex(const V& vertex); // добавление вершины
    int addVertex(const V& vertex, std::vector<E>& Edges); // добавление вершины с исходящими рёбрами
    // методы добавления вершины возвращают id вершины
    void addEdge(const E& edge); // добавление ребра
    V& getVertex(int n); // получение вершины по id
    const V& getVertex(int n) const;
    E& getEdge(int vertexFrom, int vertexTo); // получение ребра по id вершинб которые он соединяет
    const E& getEdge(int vertexFrom, int vertexTo) const;
    std::vector<E*>&& getEdgesFrom(int vertexId); // получение всех рёбер из вершины
    std::vector<const E*>&& getEdgesFrom(int vertexId) const;
    std::vector<E*>&& getEdgesTo(int vertexId); // получение всех рёбер в вершину
    std::vector<const E*>&& getEdgesTo(int vertexId) const;
    std::vector<V*>&& getNeighbors(int vertexId); // получение указателей на всех соседей
    std::vector<const V*>&& getNeighbors(int vertexId) const;
    size_t sizeV() const; // количество вершин
    size_t sizeE() const; // количество рёбер
private:
    std::vector<V> vertices;
    std::vector<E> edges;
    
};

//------------------------------------------------------------

template<class E, class V>
Graph<E, V>::Graph(){};

template<class E, class V>
Graph<E, V>::Graph(const std::vector<std::vector<E>>& graph){
    vertices.resize(graph.size());
    int vertexNumber = 0;
    int edgeNumber = 0;
    for(auto i : graph){
        for(auto j : i){
            assert(j.vertexTo < vertices.size());
            edges.push_back(j);
            edges.back().vertexFrom = vertexNumber;
            vertices[vertexNumber].vertexId = vertexNumber;
            vertices[vertexNumber].outgoingEdges.push_back(edgeNumber);
            vertices[edges.back().vertexTo].incomingEdges.push_back(edgeNumber);
            ++edgeNumber;
        }
        ++vertexNumber;
    }
}

template<class E, class V>
int Graph<E, V>::addVertex(const V& vertex){
    
    vertex.vertexId = int(vertices.size());
    vertices.push_back(vertex);
    return vertices.back().vertexId;
}

template<class E, class V>
int Graph<E, V>::addVertex(const V& vertex, std::vector<E>& vertexEdges){
    vertex.vertexId = vertices.size();
    vertices.push_back(vertex);
    for(auto& i : vertexEdges){
        i.vertexFrom = vertices.size();
        vertices[i.vertexTo].incomingEdges.push_back(edges.size());
        edges.push_back(i);
    }
    return vertices.back().vertexId;
}

template<class E, class V>
void Graph<E, V>::addEdge(const E& edge){
    vertices[edge.vertexFrom].outgoingEdges.push_back(int(edges.size()));
    vertices[edge.vertexTo].incomingEdges.push_back(int(edges.size()));
    edges.push_back(edge);
}

template<class E, class V>
V& Graph<E, V>:: getVertex(int n){
    return vertices[n];
}

template<class E, class V>
const V& Graph<E, V>:: getVertex(int n) const{
    return vertices[n];
}

template<class E, class V>
E& Graph<E, V>:: getEdge(int vertexFrom, int vertexTo){
    for(auto i: vertices[vertexFrom].outgoingEdges){
        if(edges[i].vertexTo == vertexTo)
            return edges[i];
    }
    assert(false);
}

template<class E, class V>
const E& Graph<E, V>::getEdge(int vertexFrom, int vertexTo) const{
    for(auto i: vertices[vertexFrom].outgoingEdges){
        if(edges[i].vertexTo == vertexTo)
            return edges[i];
    }
    assert(false);
}

template<class E, class V>
std::vector<E*>&& Graph<E, V>::getEdgesFrom(int vertexId){
    std::vector<E*> result;
    for(auto i : vertices[vertexId].outgoingEdges)
        result.push_back(&edges[i]);
    return move(result);
}

template<class E, class V>
std::vector<const E*>&& Graph<E, V>::getEdgesFrom(int vertexId) const{
    std::vector<const E*> result;
    for(auto i : vertices[vertexId].outgoingEdges)
        result.push_back(&edges[i]);
    return std::move(result);
}

template<class E, class V>
std::vector<E*>&& Graph<E, V>::getEdgesTo(int vertexId){
    std::vector<E*> result;
    for(auto i : vertices[vertexId].incomingEdges)
        result.push_back(&edges[i]);
    return std::move(result);
}

template<class E, class V>
std::vector<const E*>&& Graph<E, V>::getEdgesTo(int vertexId) const{
    std::vector<const E*> result;
    for(auto i : vertices[vertexId].incomingEdges)
        result.push_back(&edges[i]);
    return std::move(result);
}

template<class E, class V>
std::vector<V*>&& Graph<E, V>:: getNeighbors(int vertexId){
    std::vector<E> result;
    result.resize(vertices[vertexId].outgoingEdges.size());
    for(auto i : vertices[vertexId].outgoingEdges)
        result.push_back(&vertices[edges[i].vertexTo]);
    return std::move(result);
}

template<class E, class V>
std::vector<const V*>&& Graph<E, V>:: getNeighbors(int vertexId) const{
    std::vector<E> result;
    result.resize(vertices[vertexId].outgoingEdges.size());
    for(auto i : vertices[vertexId].outgoingEdges)
        result.push_back(&vertices[edges[i].vertexTo]);
    return std::move(result);
}
template<class E, class V>
size_t Graph<E, V>:: sizeV() const{
    return vertices.size();
}

template<class E, class V>
size_t Graph<E, V>:: sizeE() const{
    return edges.size();
}

#endif
