#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Number of vertices in the graph
const int V = 6;

// Function to find the vertex with the minimum distance value
int minDistance(const vector<int>& dist, const vector<bool>& sptSet) {
    int minDist = INT_MAX, minIndex = -1;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the shortest path from source to target
void printPath(const vector<int>& parent, int target) {
    if (parent[target] == -1) {
        cout << target;
        return;
    }

    printPath(parent, parent[target]);
    cout << " -> " << target;
}

// Function to perform Dijkstra's algorithm
void dijkstra(const vector<vector<int>>& graph, int src, int target) {
    vector<int> dist(V, INT_MAX);  // Distance from source to each vertex
    vector<bool> sptSet(V, false); // Shortest path tree set
    vector<int> parent(V, -1);     // Parent array to store the shortest path tree

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Shortest Path from " << src << " to " << target << ": ";
    printPath(parent, target);
    cout << "\nShortest Distance: " << dist[target] << endl;
}

int main() {
    vector<vector<int>> graph = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int src = 0;     // Source node
    int target = 5;  // Target node

    dijkstra(graph, src, target);

    return 0;
}
