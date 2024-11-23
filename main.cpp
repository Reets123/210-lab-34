// Lab 34: Network Graph
// COMSC-210 - Ibrahim Alatig 

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <limits>

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

        while (!s.empty()) {
            int curr = s.top();
            s.pop();

            if (visited.find(curr) == visited.end()) {
                visited.insert(curr);
                cout << "Inspecting Junction " << curr << " ";
                const char* placeType;
                switch (curr) {
                    case 0: placeType = "(Warehouse)"; break;
                    case 1: placeType = "(Distribution Hub)"; break;
                    case 2: placeType = "(Retail Store)"; break;
                    case 5: placeType = "(Customer)"; break;
                    case 6: placeType = "(Food Truck)"; break;
                    default: placeType = "(Unknown)"; break;
                }
                cout << placeType << endl;

                for (auto &neighbour : adjList[curr]) {
                    int adjVertex = neighbour.first;
                    cout << "  → Potential delivery to Junction " << adjVertex << " (Capacity: " << neighbour.second << " items)" << endl;
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
        
        cout << "Layer-by-Layer Network Inspection (BFS) from Junction " << vertex << ":" << endl;
        cout << "Purpose: Analyzing delivery routes by distance from source" << endl;
        cout << "=================================================" << endl;

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
                    cout << "  → Next delivery area: Junction " << adjVertex << " (Capacity: " << neighbour.second << " items)" << endl;
                    visited.insert(adjVertex);
                    q.push(adjVertex);
                }
            }
        }
        cout << endl;
    }

    void dijkstra(int start) {
        vector<int> dist(SIZE, numeric_limits<int>::max());
        dist[start] = 0;
        set<Pair> s;
        s.insert(make_pair(0, start));

        while (!s.empty()) {
            auto [distance, vertex] = *s.begin();
            s.erase(s.begin());

            for (const auto &neighbour : adjList[vertex]) {
                int newDist = distance + neighbour.second;

                if (newDist < dist[neighbour.first]) {
                    s.erase(make_pair(dist[neighbour.first], neighbour.first));
                    dist[neighbour.first] = newDist;
                    s.insert(make_pair(newDist, neighbour.first));
                }
            }
        }

        cout << "Shortest path from node " << start << ":" << endl;
        for (int i = 0; i < SIZE; ++i) {
            cout << start << " -> " << i << " : " << (dist[i] == numeric_limits<int>::max() ? -1 : dist[i]) << endl;
        }
    }
};

int main() {
    vector<Edge> edges = {
        {0, 1, 8}, {0, 2, 21}, 
        {1, 2, 6}, {1, 5, 5}, {1, 6, 4}, 
        {2, 9, 11}, {2, 10, 8}, 
        {6, 11, 10}, {6, 12, 15}, {6, 14, 5}, 
        {9, 13, 3}, {10, 12, 7}, {11, 14, 9}, 
        {12, 13, 3}, {13, 9, 6}
    };

    Graph graph(edges);
    graph.printGraph();

    graph.DFS(0);  
    graph.BFS(0);

    return 0;
}