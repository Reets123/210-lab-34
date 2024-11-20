// Lab 34: Network Graph
// COMSC-210 - Ibrahim Alatig 

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>

using namespace std;

const int SIZE = 7;

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
                cout << curr <