/* CSI 3334
 * Project 6 -- Network Broadcasting
 * Filename: driver-proj6.cpp
 * Student name: Gabriel Choi
 * assignment: project 6
 * due date: May 5, 2023
 * version: 1.0
 *
 * This file takes in servers from the user and their delay times to other
 * servers. Then the driver finds the smallest total delay time from a
 * server, and it outputs that delay time and server(s) to the screen.
 */

#include "arrayheap-student-proj6.h"
#include "graph-proj6.h"
#include <map>
#include <string>
#include <sstream>


using namespace std;

const int MAX = 1000000000;
const int SERVER_STRING = 7; // length of "_server"
/* isServer
 *  parameters:
 *      in: a computer's name
 *  return value: if in is a server or not
 *
 *  This function finds if the provided computer is a server.
 */
bool isServer(string in){
    if(in.find("_server", in.size() - SERVER_STRING, SERVER_STRING) == string::npos){
        return false;
    }
    return true;
}

/* main
 *  parameters: none
 *  return value: 0 (indicating a successful run)
 *
 *  This function reads in the amount of edges in the network,
 *  then counts the unique vertices from the input and determines if each vertex
 *  is a server. A graph is created and the user's edges are added. Dijkstra's
 *  algorithm is used to calculate the total delay from each vertex and the minimum
 *  total delay is stored. The valid servers with the least total delay is output.
 */
int main() {
    int count, cost, minCost = MAX, vCount = 0;
    map<string, int> edgeMap;
    vector<bool> servers;
    vector<int> delayArray;
    string comp1, comp2;
    stringstream ss;

    ss.clear();

    cin >> count;

    for(int i = 0; i < count; ++i){
        cin >> comp1 >> comp2 >> cost;
        ss << comp1 << " " << comp2 << " " << cost << endl;

        //finds if comp1 is already in map
        if(edgeMap.find(comp1) == edgeMap.end()){
            edgeMap[comp1] = vCount;
            if(isServer(comp1)){
                servers.push_back(true);
            }
            else{
                servers.push_back(false);
            }
            vCount++;
        }
        //finds if comp2 is already in map
        if(edgeMap.find(comp2) == edgeMap.end()) {
            edgeMap[comp2] = vCount;
            if (isServer(comp2)) {
                servers.push_back(true);
            } else {
                servers.push_back(false);
            }
            vCount++;
        }

    }

    //creates the graph and finds the servers
    Graph g(edgeMap.size());

    for(int i = 0; i < count; ++i){
        ss >> comp1 >> comp2 >> cost;
        g.addEdge(edgeMap[comp1], edgeMap[comp2], cost);
    }

    //find total delay for each server
    for(int i = 0; i < servers.size(); ++i){
        if(servers[i]) {
            //creates new element in array for total delay
            delayArray.push_back(0);
            vector<int> allEdge = g.dijkstra(i);
            //calculates total delay for server at i
            for(int j = 0; j < servers.size(); ++j) {
                if(allEdge[j] >= 0 && delayArray[i] < MAX){ // changed from alledge j > 0
                    delayArray[i] += allEdge[j];
                }
            }
            if(delayArray[i] >= 0){
                minCost = min(minCost, delayArray[i]);
            }
        }
        else{
            //adds inf element for non-servers
            delayArray.push_back(MAX);
        }
    }
    //checks if the graph is complete
    if(minCost >= MAX){
        cout << "no server can serve the whole network" << endl;
    }
    else{
        cout << "total delay: " << minCost << endl;
        for(map<string, int>::iterator it = edgeMap.begin();
            it != edgeMap.end(); ++it){
            int ndx = it->second;
            if(servers[ndx] && delayArray[ndx] == minCost){
                cout << it->first << endl;
            }
        }
    }

    return 0;
}