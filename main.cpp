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
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFS(int vertex) {
        set<int> visited;
        stack<int> s;
        s.push(vertex);

        while (!s.empty()) {
            int curr = s.top();
            s.pop();

            if (visited.find(curr) == visited.end()) {
                visited.insert(curr);
                cout << curr << " ";

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
        {5, 6, 10}, {5, 7, 15}, {5,
    };

    Graph graph(edges);
    graph.printGraph();

    cout << "DFS starting from vertex 0:" << endl;
    graph.DFS(0);
    
    cout << "BFS starting from vertex 0:" << endl;
    graph.BFS(0);

    return 0;
}