/* CSI 3334
 * Project 6 -- Network Broadcasting
 * Filename: graph-proj6.cpp
 * Student name: Gabriel Choi
 * assignment: project 6
 * due date: May 5, 2023
 * version: 1.0
 *
 * This file holds the code for the graph class.
 */

#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"

/* addEdge
 * parameters: from - source vertex
 *             to   - destination vertex
 *             cost - cost of edge traversal
 * return: none
 *
 * Adds edge to graph by adding the destination vertex to the
 * the source vertex's list in the adjacency list.
 */
void Graph::addEdge(int from, int to, int cost){
    if(inVertexRange(from) and inVertexRange(to)){
        adjacencyList[from].push_back(Edge(to,cost));
    }
}

/* dijkstra
 * parameters: source - The source vertex of the paths being found
 * return: A vector containing the cost to travel to each vertex from source.
 *
 * Finds the shortest paths from source to every vertex in the graph.
 */
vector<int> Graph::dijkstra(int source) const{

    vector<int> distance(this->adjacencyList.size(), INFINITE_COST),
            keys(this->adjacencyList.size(),-1);
    ArrayHeap<pair<int, int>> frontier;
    distance[source] = 0;

    pair<int, int> s = {0, source};
    keys[source] = frontier.insert(s);

    while(frontier.getNumItems() != 0){
        int currV = frontier.getMinItem().second;
        frontier.removeMinItem();

        for(auto i = adjacencyList[currV].begin();
            i != adjacencyList[currV].end(); ++i){

            auto& neighbor = *i;
            int to = neighbor.to;
            int weight = neighbor.cost;
            if(distance[currV] + weight < distance[to]){
                distance[to] = weight + distance[currV];

                if(!frontier.isOnHeap(keys[to])) {
                    keys[to] = frontier.insert({distance[to], to});
                } else {
                    frontier.changeItemAtKey(keys[to], {distance[to], to});
                }
            }
        }
    }

    return distance;
}