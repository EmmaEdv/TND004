/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }
    // *** TODO ***
    Queue<int> Q;
    //no node is visited yet, all distances should be set to infinity
    for(int i=1; i<size+1; i++){
        done[i] = false;
        dist[i] = INFINITY;
    }

    dist[s] = 0;

    Q.enqueue(s);
    while(!Q.isEmpty()){
        int v = Q.getFront();
        //cout << "jag vet vad som ligger framst i kon" << endl;
        Q.dequeue();
        //cout << "jag har dekjuat " << endl;
        Node *temp = array[v].getFirst();
       // cout << "first in list is " << temp->vertex << endl;
        //While the queued node points somewhere
        while(temp != nullptr){
            //if the node is not visited
            if(dist[v]+1 < dist[temp->vertex] ){
                cout << "temp->vertex is " << temp->vertex << " and v is " << v << endl;
                dist[temp->vertex] = dist[v]+1;
                path[temp->vertex] = (temp->vertex == s ? 0 : v);
                done[temp->vertex] = true;
                Q.enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
        Queue<int> Q;
    //no node is visited yet, all distances should be set to infinity
    for(int i=1; i<size+1; i++){
        done[i] = false;
        dist[i] = INFINITY;
    }

    dist[s] = 0;

    Q.enqueue(s);
    while(!Q.isEmpty()){
        int v = Q.getFront();
        //cout << "jag vet vad som ligger framst i kon" << endl;
        Q.dequeue();
        //cout << "jag har dekjuat " << endl;
        Node *temp = array[v].getFirst();
       // cout << "first in list is " << temp->vertex << endl;
        while(temp != nullptr){
            if(dist[v]+temp->weight < dist[temp->vertex]){
                //cout << "temp->vertex is " << temp->vertex << endl;
                dist[temp->vertex] = dist[v]+temp->weight;
                path[temp->vertex] = (temp->vertex == s ? 0 : v);
                done[temp->vertex] = true;
                Q.enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    
    // *** TODO ***
    if(dist[t] != 0){
        //store the actual value, and call recursively..
        printPath(path[t]);
    }
    cout << " " << t;
    
//    int start = 0;
//    int index = 0;
//    while(index != size){
//        if(dist[index]==0){
//            start = index;
//            break;
//        }
//        index++;
//    }
//    int itr = t;
//    int temp[dist[t]];
//    int i = dist[t];
//    cout << " " << dist[t] << endl;
//    while(i >= 0){
//        cout << "tjip: " << i << endl;
//        temp[i] = itr;
//        itr = path[itr];
//        i--;
//    }
//    for(int i = 0; i<=dist[t]; i++){
//        cout << temp[i] << " ";
//        if(i < dist[t])
//            cout << "-> ";
//    }
}
