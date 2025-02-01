#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Graph {
public:
    unordered_map<char, vector<pair<char, int>>> adjList;

    void addEdge(char u, char v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Assuming an undirected graph
    }

    void dijkstra(char start, char end) {
        unordered_map<char, int> distances;
        unordered_map<char, char> previous;
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<>> pq;

        for (auto &node : adjList) {
            distances[node.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            char current = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (current == end) break;

            for (auto &neighbor : adjList[current]) {
                char nextNode = neighbor.first;
                int edgeWeight = neighbor.second;
                int newDist = currentDist + edgeWeight;

                if (newDist < distances[nextNode]) {
                    distances[nextNode] = newDist;
                    previous[nextNode] = current;
                    pq.push({newDist, nextNode});
                }
            }
        }

        if (distances[end] == numeric_limits<int>::max()) {
            cout << "No path found from " << start << " to " << end << endl;
            return;
        }

        cout << "Shortest path cost: " << distances[end] << endl;
        cout << "Path: ";

        vector<char> path;
        char at = end;

        // Ensure 'start' is reachable by checking if 'previous' contains 'at'
        while (at != start) {
            if (previous.find(at) == previous.end()) {
                cout << "No valid path found.\n";
                return;
            }
            path.push_back(at);
            at = previous[at];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph g;
    
    // Hardcoded graph example
    g.addEdge('A', 'B', 4);
    g.addEdge('A', 'C', 2);
    g.addEdge('B', 'C', 5);
    g.addEdge('B', 'D', 10);
    g.addEdge('C', 'D', 3);
    g.addEdge('D', 'E', 8);
    g.addEdge('E', 'A', 7);

    char start, end;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the ending node: ";
    cin >> end;

    g.dijkstra(start, end);

    return 0;
}
