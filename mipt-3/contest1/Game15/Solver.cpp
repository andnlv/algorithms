//
//  Solver.cpp
//  Game15
//
//  Created by Andrey Danilov on 12.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Solver.hpp"
#include <stack>
#include <unordered_set>
#include <cassert>
#include <string>
#if s > 4
unsigned char Vertex::field::operator [] (int n) const{
    return value.operator [] (n);
}
void Vertex::field::swap(int i, int j){
    std::swap(value[i], value[j]);
}

Vertex::Vertex(std::vector<unsigned char> a){
    box.value.resize(s*s);
    for(int i = 0; i < s*s; ++i)
        box.value[i] = a[i];
    h = countHeuristic();
}
#else
unsigned char Vertex::field::operator [] (int n) const{
    return (value >> (4*n))%16;
}
void Vertex::field::swap(int i, int j){
    unsigned char a = this->operator[](i);
    unsigned char b = this->operator[](j);
    value = value - a*power16[i] + b*power16[i];
    value = value - b*power16[j] + a*power16[j];
}

Vertex::Vertex(std::vector<unsigned char> a){
    for(int i = 0; i < s*s; ++i)
        box.value += a[i]*power16[i];
    h = countHeuristic();
}

Vertex::Vertex(unsigned long a){
    box.value = a;
    h = countHeuristic();
}
#endif

int Vertex::countHeuristic() const{
    int h = 0;
    for(int i = 0; i < s*s; ++i){ // манхетенское растояние
        if(box[i] != 0)
            h += abs(int(i % s) - int((box[i] - 1) % s)) + abs(int(i / s) - int((box[i] - 1) / s));
    }
    int firstInLine;
    for(int i = 0; i < s; ++i){ // строковый конфликт
        firstInLine = 0;
        for(int j = s * i; j < s * (i + 1); ++j){
            if(box[j] != 0 && (box[j] - 1) / s == i){
                if(firstInLine == 0)
                    firstInLine = box[j];
                else if(firstInLine > box[j]){
                    h += 2;
                    firstInLine = box[j];
                    break;
                }
            }
        }
    }
    for(int i = 0; i < s; ++i){ // столбцовый конфликт
        firstInLine = 0;
        for(int j = i; j < s*s; j+=s){
            if(box[j] != 0 && (box[j] - 1) % s == i){
                if(firstInLine == 0)
                    firstInLine = box[j];
                else if(firstInLine > box[j]){
                    h += 2;
                    firstInLine = box[j];
                    break;
                }
            }
        }
    }
    
    // угловые конфликты
    if ((box[0] - 1)/s != 0 && (box[0] - 1)%s != 0 &&
        box[1] == 2 && box[s] == s + 1)
        h += 2;
    if((box[s-1]-1)/s != 0 && (box[s-1]-1)%s != s-1 &&
       box[s-2] == s-1 && box[2*s-1] == 2*s)
        h += 2;
    if((box[s*s-s]-1)/s != s-1 && (box[0]-1)%s != 0 &&
       box[s*s-2*s] == s*s-2*s+1 && box[s*s-s+1] == s*s-s+2)
        h += 2;
    if(box[s*s-1] == 0 && box[s*s-s-1] == s*s-s && box[s*s-2] == s*s-1)
        h += 2;
    return h;
}

std::vector<Direction> Vertex::availableDirections() const{
    std::vector<Direction> res;
    int i;
    for(i = 0; box[i] != 0; i++);
    if(i%s < s-1)
        res.push_back(Direction::R);
    if(i/s > 0)
        res.push_back(Direction::U);
    if(i%s > 0)
        res.push_back(Direction::L);
    if(i/s < s-1)
        res.push_back(Direction::D);
    return std::move(res);
}

Vertex Vertex::getVertex(Direction dir) const{
    field newBox = box;
    int i;
    for(i = 0; box[i] != 0; ++i);
    if(dir == Direction::R)
        newBox.swap(i, i+1);
    if(dir == Direction::U)
        newBox.swap(i, i-s);
    if(dir == Direction::L)
        newBox.swap(i, i-1);
    if(dir == Direction::D)
        newBox.swap(i, i+s);
    return Vertex(newBox.value);
}

bool Vertex::operator < (const Vertex &other) const{
    if(searchMinWay) // наилучший путь
        return h + way < other.h + other.way;
    else // любой путь
        return h < other.h;
}

bool Vertex::operator <= (const Vertex & other) const{
    return !(other < *this);
}

#if s > 4
bool Vertex::operator == (const Vertex & other) const{
    if(box.value.size() != other.box.value.size())
        return false;
    for(int i = 0; i < box.value.size(); ++i)
        if(box.value[i] != other.box.value[i])
            return false;
    return true;
}
#else
bool Vertex::operator == (const Vertex & other) const{
    return other.box.value == this->box.value;
}
#endif
#if s > 4
Vertex makeFinish(){
    std::vector<unsigned char> res(s*s);
    for(int i = 1; i < s*s; ++i){
        res[i-1] = i;
    };
    res[s*s-1] = 0;
    return res;
};
#else
Vertex makeFinish(){
    unsigned long res = 0;
    for(int i = 1; i < s*s; ++i){
        res += i*power16[i-1];
    };
    return res;
};
#endif

#if s > 4
unsigned long std::hash<Vertex>::operator()(const Vertex &v) const{
    std::string str;
    for(int i = 0; i < s*s; ++i)
        str += v.box.value[i]+'a';
    return std::hash<std::string>()(str);
};
#else
unsigned long std::hash<Vertex>::operator()(const Vertex &v) const{
    return std::hash<unsigned long>()(v.box.value);
};

#endif
void heap_swap(const Vertex*& x, const Vertex*& y){
    std::swap(x->heap_position, y->heap_position);
    std::swap(x, y);
}

void sift_up(std::vector<const Vertex*> &heap, size_t n){
    while(n > 0){
        if(*heap[(n-1)/2] <= *heap[n])
            return;
        heap_swap(heap[n], heap[(n-1)/2]);
        n = (n-1)/2;
    }
}

void sift_down(std::vector<const Vertex*> &heap, size_t n){
    while(2*n+1 < heap.size()){
        if( 2*n+2 < heap.size() ){
            if(*heap[n] <= *heap[2*n+1] &&
               *heap[n] <= *heap[2*n+2])
                return;
            else if(*heap[2*n+1] < *heap[2*n+2]){
                heap_swap(heap[n], heap[2*n+1]);
                n = 2*n+1;
            }
            else{
                heap_swap(heap[n], heap[2*n+2]);
                n = 2*n+2;
            }
        }
        else{
            if(*heap[n] <= *heap[2*n+1])
                return;
            else{
                heap_swap(heap[n], heap[2*n+1]);
                n = 2*n+1;
            }
        }
    }
}

void push_heap(std::vector<const Vertex*> &heap, const Vertex* vertex){
    vertex->heap_position = int(heap.size());
    heap.push_back(vertex);
    sift_up(heap, heap.size()-1);
};

const Vertex* pop_heap(std::vector<const Vertex*> &heap){
    std::swap(*heap.begin(), heap.back());
    heap[0]->heap_position = 0;
    heap.back()->heap_position = -1;
    const Vertex* res = heap.back();
    heap.pop_back();
    sift_down(heap, 0);
    return res;
};

#if s > 4
Vertex readInput(std::istream& in){
    std::vector<unsigned char> startBox(s*s, 0);
    for(int i = 0; i < s*s; ++i){
        int t;
        in >> t;
        startBox[i] = t;
    }
    Vertex start(startBox);
    start.way = 0;
    return start;
}
#else
Vertex readInput(std::istream& in){
    unsigned long startBox = 0;
    for(int i = 0; i < s*s; ++i){
        int t;
        in >> t;
        startBox += t*power16[i];
    }
    Vertex start(startBox);
    start.way = 0;
    return start;
}
#endif

void printAnswer(std::unordered_set<Vertex>& visitedVertices, Vertex finishVertex, std::ostream& out){
    out << finishVertex.way << "\n";
    std::stack<char> way;
    Vertex currentVertex = finishVertex;
    for(int i = 0; i < finishVertex.way; ++i){
        Direction dir = currentVertex.moveDone;
        if(dir == Direction::R){
            currentVertex = *visitedVertices.find(currentVertex.getVertex(Direction::L));
            way.push('R');
        }
        if(dir == Direction::U){
            currentVertex = *visitedVertices.find(currentVertex.getVertex(Direction::D));
            way.push('U');
        }
        if(dir == Direction::L){
            currentVertex = *visitedVertices.find(currentVertex.getVertex(Direction::R));
            way.push('L');
        }
        if(dir == Direction::D){
            currentVertex = *visitedVertices.find(currentVertex.getVertex(Direction::U));
            way.push('D');
        }
    }
    
    while(way.size() > 0){
        out << way.top();
        way.pop();
    }
    out << "\n";
};

bool isSolving(const Vertex& vertex){
    int summ = 1; // сумма беспорядков + номер строки пустой клетки, если размер поля чётный + 1
    for(int i = 0; i < s*s; ++i)
        if(vertex.box[i] == 0)
            summ += (i/s + 1)*((s+1)%2);
        else
            for(int j = i + 1; j < s*s; ++j)
                summ += (vertex.box[i] > vertex.box[j])*
                bool(vertex.box[j]);
    return summ%2;
};

bool isSolved(const Vertex& vertex){
    for(int i = 0; i < s*s; ++i){
        if(vertex.box[i] != (i+1)%(s*s))
            return false;
    }
    return true;
}

Vertex AStar(std::unordered_set<Vertex>& visitedVertices, std::vector<const Vertex*>& heap){
    while (heap.size() > 0) { // пока очередь не пуста
        const Vertex* v = pop_heap(heap); // достаём первый элемент
        for( auto direction : v->availableDirections() ){ // и для всех его соседей
            Vertex newVertex = v->getVertex(direction);
            newVertex.way = v->way + 1; // путь на 1 больше
            if( visitedVertices.count(newVertex) == 0 ){ // если ещё не встречался
                newVertex.moveDone = direction; // задаём движение
                push_heap(heap, &*visitedVertices.insert(newVertex).first); // добавляем в очередь
            }
            else if( visitedVertices.find(newVertex)->way > newVertex.way && // если встречался и путь стал лучше и старый элемент ещё в очереди
                    visitedVertices.find(newVertex)->heap_position != -1){
                visitedVertices.find(newVertex)->way = newVertex.way; // обновляем вершину в очереди
                visitedVertices.find(newVertex)->moveDone = direction;
                sift_up(heap, visitedVertices.find(newVertex)->heap_position); // поднимаем с учётом нового приоритета
            }
            if( newVertex == finishVertex){ // если дошли до конечной вершины
                return newVertex; // возвращаем её
            }
        }
    }
    assert(0);
}

