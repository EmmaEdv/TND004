/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
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
    size  = n;
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
//    bool cloud[size+1];

    for(int i=1; i<size+1; i++){
        done[i] = false;
        dist[i] = INFINITY;
        path[i] = 0;
    }

    int nextNode= 1;
    dist[nextNode] = 0;
    done[nextNode] = true;
    int i = 1;

    bool allVisited = false;

    //for(int i = 1; i < size+1; i++){
    while(!done[1]){
        //1. Adding a node to the cloud
        cout << "nextNode is: " << nextNode << endl;
        done[nextNode] = true;
        int nextCloudMember = INFINITY;
        //Loop through all connecting edges of the cloud
        for(int i = 1; i < size+1; i++){
            //cout << " Iteration no: " << i;
            if(done[i]){
                cout << " node " << i << " is searching.. " << endl;
                Node *temp = array[i].getFirst();
                while (temp != nullptr && !done[temp->vertex]){
                    cout << " HEJ cloud: " << temp->vertex << endl;
                    path[temp->vertex] = nextNode;
                    dist[temp->vertex] = temp->weight;
                    //Save closest neighbor to the cloud
                    //kolla närmsta vägen till de grannar till noden som ej är visited
                    //nextCloudMember = closestNeighbor;
                    temp = temp->next;
                }
            }
            done[4] = true;
        }
    }

//
//    while(i <= size +1){
//        cout << " Iteration no: " << i;
//        if(done[nextNode]){
//            //for each node where done is true
//            //iterate over their connections
//            cout << nextNode << " is in the cloud. " << endl;
//            Node *temp = array[nextNode].getFirst();
//             nextNode = ((dist[temp->vertex] < dist[nextNode] && !done[temp->vertex]) ? temp->vertex : nextNode);
//            while(temp != nullptr){
//                //if the connected node is undone
//                //prepare the node
//                cout << "This node is " << temp->vertex << " ";
//                if(!done[temp->vertex]){
//                    path[temp->vertex] = nextNode;
//                    dist[temp->vertex] = temp->weight;
//                    //cout << "Distance: " << dist[temp->vertex] << endl;
//                    nextNode = ((dist[temp->vertex] < dist[nextNode] && !done[temp->vertex]) ? temp->vertex : nextNode);
//                    cout << "Next node is: " << nextNode << " "<< endl;
//                }
//                temp = temp->next;
//            }
//            cout << "finally, nextNode is: " << nextNode << endl;
//            done[nextNode] = true;
//        }
//        i++;
//    }

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
