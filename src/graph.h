#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "list.h"

template <class T>
struct GraphNode;

template <class T>
struct GraphEdge
{
    GraphEdge(float _weight, GraphNode<T>* _adjacent){weight = _weight; adjacent = _adjacent;}
    float weight;
    GraphNode<T>* adjacent;
};

template <class T>
struct GraphNode
{
    GraphNode(T _val){val = _val;}
    T val;
    LinkedList<GraphEdge<T>*> adjacents;
};

template <class T>
class Graph
{
public:
    Graph(){this->nodeCnt = 0;}
    ~Graph();

    bool AddNode(T val);
    bool RemoveNode(GraphNode<T>* node);

    bool AddEdge(GraphNode<T>* node, GraphNode<T>* node2, float weight = 1);
    bool RemoveEdge(GraphNode<T>* node, GraphNode<T>* node2);
    bool hasEdgre(GraphNode<T>* node, GraphNode<T>* node2);

    bool print();
    bool isEmpty(){return nodeCnt <= 0;}
private:
    LinkedList<GraphNode<T>*> nodes;
    size_t nodeCnt;
};

template <class T>
Graph<T>::~Graph()
{

}

template <class T>
bool Graph<T>::AddNode(T val)
{
    GraphNode<T> * tmp = new(nothrow) GraphNode<T>(val);
    if(!tmp)
    {
        return false;
    }
    this->nodes.AddAtEnd(tmp);
    this->nodeCnt++;

    return true;
}

template <class T>
bool Graph<T>::RemoveNode(GraphNode<T>* node)
{

    return true;
}

template <class T>
bool Graph<T>::AddEdge(GraphNode<T>* node, GraphNode<T>* node2, float weight)
{

}

template <class T>
bool Graph<T>::RemoveEdge(GraphNode<T>* node, GraphNode<T>* node2)
{


    return true;
}

template <class T>
bool Graph<T>::print()
{

    return true;
}

#endif // GRAPH_H_INCLUDED
