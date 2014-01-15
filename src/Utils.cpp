#include "Utils.h"

struct dotIters
{
    dotIters()
    {
        horiz = NULL;
        vertic = NULL;
    }
    bool AddEdge(Graph<LinkedList<dot> >& graph)
    {
        if(horiz != NULL && vertic != NULL)
            return graph.AddEdge(horiz, vertic);
        else
            return true;
    }

    Graph<LinkedList<dot> >::GraphNode* horiz;
    Graph<LinkedList<dot> >::GraphNode* vertic;
};

bool initIterMap (charMap& map, Graph<LinkedList<dot> >& graph, dotIters *** iterMap)
{
    *iterMap = new(nothrow) dotIters*[map.getWidth()];
    if(!(*iterMap))
    {
        return false;
    }
    for(int i = 0; i < map.getWidth(); ++i)
    {
        (*iterMap)[i] = new(nothrow) dotIters[map.getHeigth()];
        if(!(*iterMap)[i])
        {
            for(int j = 0; j < i; ++j)
            {
                delete (*iterMap)[j];
            }
            delete[] (*iterMap);
            return false;
        }
    }
    return true;
}

bool addGraphEdges(Graph<LinkedList<dot> >& graph, dotIters ** iterMap, int width, int heigth)
{
    for(int i = 0; i < width; ++i)
    {
        for(int j = 0; j < heigth; ++j)
        {
            if(!iterMap[i][j].AddEdge(graph))
            {
                return false;
            }
        }
    }
    return true;
}

void clearIterMap(dotIters ** iterMap, int width)
{
    for(int i = 0; i < width; ++i)
    {
        delete[] iterMap[i];
    }
    delete[] iterMap;
}

bool isSingleDot(charMap& map, dot a)
{
    if(map.isFree(dot(a.x - 1, a.y)) || map.isFree(dot(a.x + 1, a.y))
       || map.isFree(dot(a.x, a.y - 1)) || map.isFree(dot(a.x, a.y + 1)))
        return false;
    return true;
}

bool fillRowNode(charMap& map, Graph<LinkedList<dot> >& graph,
        dot start, dotIters ** iterMap, bool rowOrCol)//truq == row , false == col
{
    int end = rowOrCol?map.getWidth():map.getHeigth();
    for(; (rowOrCol?start.x:start.y) < end; rowOrCol?++start.x:++start.y)
    {
        if(!map.isFree(start))
        {
            continue;
        }
        if(isSingleDot(map, start) && rowOrCol)
        {
            graph.AddNode(LinkedList<dot>());
            LinkedList<Graph<LinkedList<dot> >::GraphNode*>::LLiterator iter = graph.GetNodeIterEnd();
            --iter;
            (*iter)->val.AddAtEnd(start);
            iterMap[start.x][start.y].horiz = *iter;

            continue;
        }

        int cntFreeDots = 0;
        dot tmp(start.x, start.y);
        while(map.isFree(tmp))
        {
            ++cntFreeDots;
            rowOrCol?++tmp.x:++tmp.y;
        }

        if(cntFreeDots == 1)
        {
            continue;
        }

        graph.AddNode(LinkedList<dot>());
        LinkedList<Graph<LinkedList<dot> >::GraphNode*>::LLiterator iter = graph.GetNodeIterEnd();
        --iter;
        while(map.isFree(start))
        {
            (*iter)->val.AddAtEnd(start);
            if(rowOrCol)
            {
                iterMap[start.x][start.y].horiz = *iter;
            }
            else
            {
                iterMap[start.x][start.y].vertic = *iter;
            }
            rowOrCol?++start.x:++start.y;
        }
    }

    return true;
}

bool fromBoolMapToGraph(charMap& map, Graph<LinkedList<dot> >& graph)
{
    dot iter;
    dotIters ** iterMap;

    if(!initIterMap(map, graph, &iterMap))
    {
        return false;
    }

    for(int i = 0; i < map.getWidth(); ++i)
    {
        if(!fillRowNode(map, graph, dot(i,0), iterMap , false))
        {
            return false;
        }
    }


    for(int i = 0; i < map.getHeigth(); ++i)
    {
        if(!fillRowNode(map, graph, dot(0,i), iterMap, true))
        {
            return false;
        }
    }

    if(!addGraphEdges(graph, iterMap, map.getWidth(), map.getHeigth()))
    {
        return false;
    }

    clearIterMap(iterMap, map.getWidth());
    return true;
}

