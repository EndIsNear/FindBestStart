#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "list.h"


template <class T>
class Graph
{

    struct GraphNode;
    typedef Graph<T>::GraphNode GraphNode;

    struct GraphEdge
    {
        GraphEdge(float _weight, GraphNode* _adjacent){weight = _weight; adjacent = _adjacent;}
        float weight;
        GraphNode* adjacent;
    };

    typedef Graph<T>::GraphEdge GraphEdge;
    typedef typename LinkedList<GraphNode*>::LLiterator IterPtrGrNode;
    typedef typename LinkedList<GraphEdge*>::LLiterator IterPtrGrEdge;

    struct GraphNode
    {
        GraphNode(T _val){val = _val;}
        T val;
        LinkedList<GraphEdge*> adjacents;
    };


    LinkedList<GraphNode*> nodes;
    size_t nodeCnt;

    char GetCharForNode(GraphNode** index,const GraphNode* node)const
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
public:

    Graph(){this->nodeCnt = 0;}
    ~Graph()
    {
        IterPtrGrNode it = this->nodes.GetItBegin();
        IterPtrGrNode itEnd = this->nodes.GetItEnd();
        while(it != itEnd)
        {
            this->RemoveNode(it);
            ++it;
        }
    }

    bool AddNode(T val)
    {
        GraphNode * tmp = new(nothrow) GraphNode(val);
        if(!tmp)
        {
            return false;
        }
        this->nodes.AddAtEnd(tmp);
        this->nodeCnt++;

        return true;
    }

    bool RemoveNodeEdges(GraphNode* node)
    {
        IterPtrGrEdge edgeIter = node->adjacents.GetItBegin();
        IterPtrGrEdge edgeEnd = node->adjacents.GetItEnd();
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

    bool RemoveNode(IterPtrGrNode node)
    {
        if(!this->RemoveNodeEdges(*node))
        {
            return false;
        }
        this->nodes.Remove(node);
        --this->nodeCnt;

        return true;
    }

    bool AddEdge(IterPtrGrNode left, IterPtrGrNode right, float weight = 1)
    {
        return this->AddEdge(*left, *right, weight);
    }

    bool AddEdge(GraphNode* left, GraphNode* right, float weight = 1)
    {
        GraphEdge* tmp = new(nothrow) GraphEdge(weight, right);
        if(!tmp)
        {
            return false;
        }
        left->adjacents.AddAtEnd(tmp);

        tmp = new(nothrow) GraphEdge(weight, left);
        if(!tmp)
        {
            return false;
        }
        right->adjacents.AddAtEnd(tmp);

        return true;
    }

    bool RemoveEdge(IterPtrGrNode left, IterPtrGrNode right)
    {
        return this->RemoveEdge(*left, *right);
    }

    bool RemoveEdge(GraphNode* left, GraphNode* right)
    {
        if(!this->hasEdge(left, right))
        {
            return false;
        }
        IterPtrGrEdge edgeIter = left->adjacents.GetItBegin();
        IterPtrGrEdge edgeEnd = left->adjacents.GetItEnd();
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

    bool hasEdge(IterPtrGrNode left, IterPtrGrNode right)const
    {
        return this->hasEdge(*left, *right);
    }

    bool hasEdge(GraphNode* left, GraphNode* right)const
    {
        bool leftRight = false, rightLeft = false;
        IterPtrGrEdge edgeIter = left->adjacents.GetItBegin();
        IterPtrGrEdge edgeEnd = left->adjacents.GetItEnd();
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

    bool print()const
    {
        GraphNode** index = new(nothrow) GraphNode*[this->nodeCnt];
        if(!index)
        {
            return false;
        }
        IterPtrGrNode iter = this->nodes.GetItBegin();
        IterPtrGrNode itEnd = this->nodes.GetItEnd();

        for(unsigned cnt = 0; iter!= itEnd; cnt++, ++iter)
        {
            index[cnt] = *iter;
        }
        iter = this->nodes.GetItBegin();
        while(iter != itEnd)
        {
            cout << this->GetCharForNode(index, *iter) << " - ";
            cout << (*iter)->val << ":";
            IterPtrGrEdge edgeIter = (*iter)->adjacents.GetItBegin();
            IterPtrGrEdge edgeEnd = (*iter)->adjacents.GetItEnd();
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

    bool isEmpty()const
    {
        return nodeCnt <= 0;
    }
};

#endif // GRAPH_H_INCLUDED
