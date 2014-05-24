/*********************************************
* file: ~\tnd004\lab\lab4b\graph.h *
* remark:implementation of undirected graphs *
* file for students *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
    int dist[size+1];
    bool done[size+1];
    int path[size+1];
    Edge edges[size];

    for(int i=0; i<size+1; i++){
        done[i] = false;
        dist[i] = INFINITY;
        path[i] = 0;
    }

    int nextNode= 1;
    dist[nextNode] = 0;
    done[nextNode] = true;
    int nextCloudMember = 0;
    int nEdges = 0;
    
    while(nEdges < size-1){
        //1. Adding a node to the cloud
        done[nextNode] = true;
        nextCloudMember = 0;
        //Loop through all connecting edges of the cloud
        for(int i = 1; i < size+1; i++){
            if(done[i]){
                Node *temp = array[i].getFirst();
                while (temp != nullptr){
                    //loop trough the connections of the node
                    if(!done[temp->vertex]){
                        //if a shorter path is found, update
                        if(temp->weight < dist[temp->vertex]){
                            path[temp->vertex] = i;
                            dist[temp->vertex] = temp->weight;
                        }
                        //Save closest neighbor to the cloud
                        nextCloudMember = dist[temp->vertex] < dist[nextCloudMember] ? temp->vertex : nextCloudMember;

                    }
                    temp = temp->next;
                }
            }
        }
        
        edges[nEdges] = Edge(nextCloudMember, path[nextCloudMember], dist[nextCloudMember]);
        nextNode = nextCloudMember;
        cout << "END OF LOOP:\n next: "<< nextCloudMember << " tail: " << path[nextCloudMember] << " weight: " << dist[nextCloudMember] <<endl;
        nEdges++;
    }
    for(int i = 0; i<size+1; i++){
        cout << edges[i] << endl;
    }
}
// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
    //Max no of edges is size
//    Heap H;
    DSets D(size+1);

//    H.Heap(size);

    int counter = 0;

    while (counter < size){

    }
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex adjacency list " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
