#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("small.txt", G);

    for (int source = 0; source < G.numVertices; ++source) {
        cout << "Source vertex: " << source << endl;

        vector<int> previous(G.numVertices, -1);
        vector<int> distances = dijkstra_shortest_path(G, source, previous);

        // Loop through all vertices to print the shortest path from source
        for (int destination = 0; destination < G.numVertices; ++destination) {
            if (source != destination) {
                vector<int> path = extract_shortest_path(distances, previous, destination);
                int totalWeight = distances[destination];
                print_path(path, totalWeight);
            }
        }
    }

    return 0;
}