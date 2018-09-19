//
//  Algorithm.hpp
//  Floid
//
//  Created by Andrey Danilov on 14.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <iostream>
#include "Graph.hpp"

void readGraph(Graph<WEdge, GraphVertex>& graph, std::istream& in); // считываем граф
void Floid(Graph<WEdge>& g, std::ostream &out); // ищем отрицательные циклы

#endif /* Algorithm_hpp */
