#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Parallel BFS using OpenMP
void parallelBFS(vector<vector<int> >& graph,
                 int start,
                 int vertices) {

    vector<bool> visited(vertices, false);

    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {

            int adjNode = graph[node][i];

            if (!visited[adjNode]) {

                #pragma omp critical
                {
                    if (!visited[adjNode]) {

                        visited[adjNode] = true;
                        q.push(adjNode);
                    }
                }
            }
        }
    }
}

int main() {

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<int> > graph(vertices);

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected Graph
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    double startTime = omp_get_wtime();

    parallelBFS(graph, start, vertices);

    double endTime = omp_get_wtime();

    cout << "\nTime Taken: "
         << endTime - startTime
         << " seconds\n";

    return 0;
}


// Sample Input:
// Enter number of vertices: 5
// Enter number of edges: 4
// Enter edges (u v):
// 0 1
// 0 2
// 1 3
// 2 4
// Enter starting vertex: 0
//
// Sample Output:
//
// BFS Traversal: 0 1 2 3 4
// Time Taken: 0.000123 seconds
