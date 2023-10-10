#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Structure to represent a city
struct City {
    string name;
    vector<pair<int, City*>> neighbors; // Pair represents distance and neighbor city pointer
};

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(map<string, City>& graph, string startCity, string destinationCity) {
    map<string, int> distance;
    map<string, string> previous;

    for (auto& city : graph) {
        distance[city.first] = INF;
    }

    distance[startCity] = 0;

    while (!graph.empty()) {
        string currentCityName;
        int minDist = INF;

        for (auto& city : graph) {
            if (distance[city.first] < minDist) {
                minDist = distance[city.first];
                currentCityName = city.first;
            }
        }

        City& currentCity = graph[currentCityName];
        graph.erase(currentCityName);

        for (auto& neighbor : currentCity.neighbors) {
            int alt = distance[currentCityName] + neighbor.first;
            if (alt < distance[neighbor.second->name]) {
                distance[neighbor.second->name] = alt;
                previous[neighbor.second->name] = currentCityName;
            }
        }
    }

    // Print the shortest path
    cout << "Shortest path from " << startCity << " to " << destinationCity << ": ";
    string current = destinationCity;
    while (current != startCity) {
        cout << current << " <- ";
        current = previous[current];
    }
    cout << startCity << endl;
    cout << "Total distance: " << distance[destinationCity] << " units" << endl;
}

int main() {
    map<string, City> graph;

    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    // Create cities and their connections
    for (int i = 0; i < numCities; ++i) {
        City city;
        cout << "Enter the name of city " << i + 1 << ": ";
        cin >> city.name;
        graph[city.name] = city;

        int numNeighbors;
        cout << "Enter the number of neighbors for " << city.name << ": ";
        cin >> numNeighbors;

        for (int j = 0; j < numNeighbors; ++j) {
            string neighborName;
            int distance;
            cout << "Enter neighbor " << j + 1 << " name and distance: ";
            cin >> neighborName >> distance;

            if (graph.find(neighborName) != graph.end()) {
                graph[city.name].neighbors.push_back({distance, &graph[neighborName]});
            }
        }
    }

    // Get user input for the starting and destination cities
    string startCity, destinationCity;
    cout << "Enter the starting city: ";
    cin >> startCity;
    cout << "Enter the destination city: ";
    cin >> destinationCity;

    dijkstra(graph, startCity, destinationCity);

    return 0;
}
