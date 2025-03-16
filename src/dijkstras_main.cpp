#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("small.txt", G);

    int src = 0;
    vector<int> previous(G.numVertices, -1);

    vector<int> distances = dijkstra_shortest_path(G, src, previous);

    for (int source = 0; source < G.numVertices; ++source) {
         vector<int> path = extract_shortest_path(distances, previous, source);
         print_path(path, distances[source]);
    }

    return 0;
}