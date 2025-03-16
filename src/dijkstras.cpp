#include "dijkstras.h"

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
     vector<int> path;
    if (distances[destination] == INF) return path;

    for (int at = destination; at != -1; at = previous[at])
        path.insert(path.begin(), at);

    return path;
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    previous[source] = -1;
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    minHeap.push({0, source});

    while(!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge: G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path found\n";
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << " ";
    }
    cout << "Total cost is " << total << endl;
}
