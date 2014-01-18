#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "graph.h"
#include "CharMap.h"
#include "heap.h"

bool fromBoolMapToGraph(charMap& map, Graph<LinkedList<dot> >& graph);

bool findBestNodes(Graph<LinkedList<dot> >& graph);

#endif // UTILS_H_INCLUDED
