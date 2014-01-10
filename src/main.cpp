#include <iostream>
#include <cstdlib>

#include "Utils.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        if(argc < 2)
        {
            cout << "Too few arguments.Need map file." << endl;
        }
        else
        {
            cout << "Too many arguments.Need only map file." << endl;
        }
        return 1;
    }

    boolMap map;
    map.fillMapFromFile(argv[1]);
    map.printMap();
    cout << endl;

    Graph<int> gr;
    gr.AddNode(15);
    gr.AddNode(113);
    LinkedList<Graph<int>::GraphNode*>::LLiterator iter = gr.GetNodeIterBegin();
    LinkedList<Graph<int>::GraphNode*>::LLiterator iter2 = gr.GetNodeIterBegin();
    iter2++;
    //gr.AddEdge(iter, iter2);

    //gr.print();
    return 0;
}
