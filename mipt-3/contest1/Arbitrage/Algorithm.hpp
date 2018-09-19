//
//  Algorithm.hpp
//  Arbitrage
//
//  Created by Andrey Danilov on 07.10.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "Graph.hpp"

void readGraph(Graph<WEdge, GraphVertex>& graph); // считывает граф
bool searching_for_cycles(Graph<WEdge> g); // ищет циклы отрицательного веса

#endif /* Algorithm_h */
