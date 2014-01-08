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

    bool RemoveNodeEdges(GraphNode<T>* node);
    bool RemoveNode(LLiterator<GraphNode<T>*> node);

    bool AddEdge(LLiterator<GraphNode<T>*> left, LLiterator<GraphNode<T>*> right, float weight = 1);
    bool AddEdge(GraphNode<T>* left, GraphNode<T>* right, float weight = 1);

    bool RemoveEdge(LLiterator<GraphNode<T>*> left, LLiterator<GraphNode<T>*> right);
    bool RemoveEdge(GraphNode<T>* left, GraphNode<T>* right);

    bool hasEdge(LLiterator<GraphNode<T>*> left, LLiterator<GraphNode<T>*> right);
    bool hasEdge(GraphNode<T>* left, GraphNode<T>* right);

    LinkedList<GraphNode<T>*> * GetListOfNodes(){return &this->nodes;}

    bool print();
    bool isEmpty(){return nodeCnt <= 0;}
private:
    LinkedList<GraphNode<T>*> nodes;
    size_t nodeCnt;

    char GetCharForNode(GraphNode<T>** index, GraphNode<T>* node);
};

template <class T>
Graph<T>::~Graph()
{
    LLiterator<GraphNode<T>*> it = this->nodes.GetItBegin();
    LLiterator<GraphNode<T>*> itEnd = this->nodes.GetItEnd();
    while(it != itEnd)
    {
        this->RemoveNode(it);
        ++it;
    }
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
bool Graph<T>::RemoveNodeEdges(GraphNode<T>* node)
{
    LLiterator<GraphEdge<T>*> edgeIter = node->adjacents.GetItBegin();
    LLiterator<GraphEdge<T>*> edgeEnd = node->adjacents.GetItEnd();
    while(edgeIter != edgeEnd)
    {
        if(!this->RemoveEdge(node, (*edgeIter)->adjacent ))
        {
            return false;
        }
        ++edgeIter;
    }

    return true;
}

template <class T>
bool Graph<T>::RemoveNode(LLiterator<GraphNode<T>*> node)
{
    if(!this->RemoveNodeEdges(*node))
    {
        return false;
    }
    this->nodes.Remove(node);
    --this->nodeCnt;

    return true;
}

template <class T>
bool Graph<T>::AddEdge(GraphNode<T>* left, GraphNode<T>* right, float weight)
{
    GraphEdge<T>* tmp = new(nothrow) GraphEdge<T>(weight, right);
    if(!tmp)
    {
        return false;
    }
    left->adjacents.AddAtEnd(tmp);

    tmp = new(nothrow) GraphEdge<T>(weight, left);
    if(!tmp)
    {
        return false;
    }
    right->adjacents.AddAtEnd(tmp);

    return true;
}

template <class T>
bool Graph<T>::AddEdge(LLiterator<GraphNode<T>*> left, LLiterator<GraphNode<T>*> right, float weight)
{
    return this->AddEdge(*left, *right, weight);
}

template <class T>
bool Graph<T>::RemoveEdge(GraphNode<T>* left, GraphNode<T>* right)
{
    if(!this->hasEdge(left, right))
    {
        return false;
    }
    LLiterator<GraphEdge<T>*> edgeIter = left->adjacents.GetItBegin();
    LLiterator<GraphEdge<T>*> edgeEnd = left->adjacents.GetItEnd();
    while(edgeIter != edgeEnd)
    {
        if((*edgeIter)->adjacent == right)
        {
            delete (*edgeIter);
            left->adjacents.Remove(edgeIter);
            break;
        }
        ++edgeIter;
    }

    edgeIter = right->adjacents.GetItBegin();
    edgeEnd = right->adjacents.GetItEnd();
    while(edgeIter != edgeEnd)
    {
        if((*edgeIter)->adjacent == left)
        {
            delete (*edgeIter);
            right->adjacents.Remove(edgeIter);
            break;
        }
        ++edgeIter;
    }

    return true;
}

template <class T>
bool Graph<T>::RemoveEdge(LLiterator<GraphNode<T>*> left, LLiterator<GraphNode<T>*> right)
{
    return this->RemoveEdge(*left, *right);
}

template <class T>
bool Graph<T>::hasEdge(GraphNode<T>* left, GraphNode<T>* right)
{
    bool leftRight = false, rightLeft = false;
    LLiterator<GraphEdge<T>*> edgeIter = left->adjacents.GetItBegin();
    LLiterator<GraphEdge<T>*> edgeEnd = left->adjacents.GetItEnd();
    while(edgeIter != edgeEnd)
    {
        if((*edgeIter)->adjacent == right)
        {
            leftRight = true;
            break;
        }
        ++edgeIter;
    }

    edgeIter = right->adjacents.GetItBegin();
    edgeEnd = right->adjacents.GetItEnd();
    while(edgeIter != edgeEnd)
    {
        if((*edgeIter)->adjacent == left)
        {
            rightLeft = true;
            break;
        }
        ++edgeIter;
    }

    return leftRight && rightLeft;
}

template <class T>
bool Graph<T>::hasEdge(LLiterator<GraphNode<T>*> left, LLiterator<GraphNode<T>*> right)
{
    return this->hasEdge(*left, *right);
}

template <class T>
bool Graph<T>::print()
{
    GraphNode<T>** index = new(nothrow) GraphNode<T>*[this->nodeCnt];
    if(!index)
    {
        return false;
    }
    LLiterator<GraphNode<T>*> iter = this->nodes.GetItBegin();
    LLiterator<GraphNode<T>*> itEnd = this->nodes.GetItEnd();

    for(unsigned cnt = 0; iter!= itEnd; cnt++, ++iter)
    {
        index[cnt] = *iter;
    }
    iter = this->nodes.GetItBegin();
    while(iter != itEnd)
    {
        cout << this->GetCharForNode(index, *iter) << " - ";
        cout << (*iter)->val << ":";
        LLiterator<GraphEdge<T>*> edgeIter = (*iter)->adjacents.GetItBegin();
        LLiterator<GraphEdge<T>*> edgeEnd = (*iter)->adjacents.GetItEnd();
        while(edgeIter != edgeEnd)
        {
            cout << this->GetCharForNode(index, (*edgeIter)->adjacent) << "[" << (*edgeIter)->weight << "]"<< " ";
            ++edgeIter;
        }
        cout << endl;
        ++iter;
    }
    for(unsigned cnt = 0; cnt < this->nodeCnt; ++cnt)
    {
        delete index[cnt];
    }
    delete[] index;

    return true;
}

template<class T>
char Graph<T>::GetCharForNode(GraphNode<T>** index, GraphNode<T>* node)
{
    for(unsigned cnt = 0; cnt < this->nodeCnt; cnt++)
    {
        if(index[cnt] == node)
        {
            return (char)(cnt + 'A');
            break;
        }
    }
    return '0';
}
#endif // GRAPH_H_INCLUDED
