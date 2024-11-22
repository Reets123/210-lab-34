// Lab 34: Network Graph
// COMSC-210 - Ibrahim Alatig 

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>

using namespace std;

const int SIZE = 15;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

      Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Delivery Network Topology:" << endl;
        cout << "================================" << endl;
        cout << "Facility connections:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Junction " << i << " connects to:";
            for (Pair v : adjList[i]) {
                const char* placeType;
                switch (i) {
                    case 0: placeType = "Warehouse"; break;
                    case 1: placeType = "Distribution Hub"; break;
                    case 2: placeType = "Retail Store"; break;
                    case 5: placeType = "Customer"; break;
                    case 6: placeType = "Food Truck"; break;
                    case 9: placeType = "Supplier"; break;
                    case 10: placeType = "Regional Hub"; break;
                    case 11: placeType = "Processing Facility"; break;
                    case 12: placeType = "Storage Facility"; break;
                    case 13: placeType = "Client"; break;
                    case 14: placeType = "Vendor"; break;
                    default: placeType = "Unknown"; break;
                }
                cout << " → Junction " << v.first << " (" << placeType << ", Capacity: " << v.second << " items) ";
            }
            cout << endl;
        }
    }

    void DFS(int vertex) {
        set<int> visited;
        stack<int> s;
        s.push(vertex);

        cout << "Network Trace (DFS) from Junction " << vertex << ":" << endl;
        cout << "Purpose: Tracing delivery paths through the network" << endl;
        cout << "======================================" << endl;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            const char* placeType;
            switch (curr) {
                case 0: placeType = "(Warehouse)"; break;
                case 1: placeType = "(Distribution Hub)"; break;
                case 2: placeType = "(Retail Store)"; break;
                case 5: placeType = "(Customer)"; break;
                case 6: placeType = "(Food Truck)"; break;
                default: placeType = "(Unknown)"; break;
            }
            cout << "Checking Junction " << curr << " " << placeType << endl;


                for (auto &neighbour : adjList[curr]) {
                    int adjVertex = neighbour.first;
                    if (visited.find(adjVertex) == visited.end()) {
                        s.push(adjVertex);
                    }
                }
            }
        }
        cout << endl;
    }

    void BFS(int vertex) {
        set<int> visited;
        queue<int> q;
        visited.insert(vertex);
        q.push(vertex);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (auto &neighbour : adjList[curr]) {
                int adjVertex = neighbour.first;
                if (visited.find(adjVertex) == visited.end()) {
                    visited.insert(adjVertex);
                    q.push(adjVertex);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0, 1, 8}, {0, 2, 21}, 
        {1, 2, 6}, {1, 3, 5}, {1, 4, 4}, 
        {2, 7, 11}, {2, 8, 8}, 
        {3, 5, 9}, 
        {5, 6, 10}, {5, 7, 15}, {5, 8, 5}, 
        {6, 7, 3}, {6, 8, 7}, 
        {7, 2, 11}, 
        {9, 10, 4}, {10, 11, 6}, {11, 12, 5}, 
        {12, 13, 7}, {13, 14, 9}, {14, 9, 3}
    };

    Graph graph(edges);
    graph.printGraph();

    cout << "DFS starting from vertex 0:" << endl;
    graph.DFS(0);
    
    cout << "BFS starting from vertex 0:" << endl;
    graph.BFS(0);

    return 0;
}