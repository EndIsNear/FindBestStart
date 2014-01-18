#include "Utils.h"


//FromMapToGraph
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

//Dijkstra part

typedef LinkedList<Graph<LinkedList<dot> >::GraphNode*>::LLiterator GraphNodeIter;
typedef LinkedList<Graph<LinkedList<dot> >::GraphEdge*>::LLiterator GraphEdgeIter;

int Dijkstra (Graph<LinkedList<dot> >& graph, GraphNodeIter iter)
{
    Heap<GraphNodeIter> heap;
    int nodeCnt = graph.getSize();
    if(nodeCnt <= 1)
    {
        return -1;
    }

    int* dist = new(nothrow) int[nodeCnt];
    if(!dist)
    {
        return -1;
    }

    for(int i = 0; i < nodeCnt; ++i)
    {
        dist[i] = INT_MAX;
    }

    heap.Push(iter, 0);
    dist[graph.GetNodeNum(iter)] = 0;
    while(!heap.IsEmpty())
    {
        int crnWeight = heap.GetTopWeight();
        iter = heap.Pop();

        GraphEdgeIter edgeIter = (*iter)->adjacents.GetItBegin();
        GraphEdgeIter edgeEnd = (*iter)->adjacents.GetItEnd();

        while(edgeIter != edgeEnd)
        {
            if(dist[graph.GetNodeNum(edgeIter)] > crnWeight + (*edgeIter)->weight)
            {
                dist[graph.GetNodeNum(edgeIter)] = crnWeight + (*edgeIter)->weight;
                GraphNodeIter tmp = graph.EdgeIterToNodeIter(edgeIter);

                iter = graph.EdgeIterToNodeIter(edgeIter);
                heap.Push(iter, dist[graph.GetNodeNum(edgeIter)]);

                //cout << dist[graph.GetNodeNum(edgeIter)] << " - " << (char)('A' + graph.GetNodeNum(edgeIter)) << endl;
            }

            ++edgeIter;
        }
    }
    int max = dist[0];
    for(int i = 0; i < nodeCnt; ++i)
    {
        if(dist[i] == INT_MAX)
        {
            delete[] dist;
            return -1;
        }
        else if(dist[i] > max)
        {
            max = dist[i];
        }
    }

    delete[] dist;
    return max;
}


bool findBestNodes(Graph<LinkedList<dot> >& graph)
{
    GraphNodeIter iter = graph.GetNodeIterBegin();

    int nodeCnt = graph.getSize();
    int* maxDist = new(nothrow) int[nodeCnt];
    if(!maxDist)
    {
        return false;
    }

    int result;
    for(int i = 0; i < nodeCnt; ++i, ++iter)
    {
        result = Dijkstra(graph, iter);
        if(result == -1)
        {
            cerr << "Unsuitable Labyrinth!" << endl;
            return false;
        }
        else
        {
            maxDist[i] = result;
            cout << "Max:" << maxDist[i] << " - " << (*iter)->val << endl;
        }
    }

    return true;
}
