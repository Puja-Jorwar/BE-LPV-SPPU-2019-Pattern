#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void parallelDFS(vector<vector<int>>& graph, int start, int vertices) {

    vector<bool> visited(vertices, false);
    stack<int> st;

    st.push(start);

    cout << "\nParallel DFS Traversal: ";

    while (!st.empty()) {

        int node;

        #pragma omp critical
        {
            if (!st.empty()) {
                node = st.top();
                st.pop();
            }
        }

        if (!visited[node]) {

            visited[node] = true;

            cout << node << " ";

            // Parallel neighbor traversal
            #pragma omp parallel for
            for (int i = 0; i < graph[node].size(); i++) {

                int neighbor = graph[node][i];

                if (!visited[neighbor]) {

                    #pragma omp critical
                    {
                        st.push(neighbor);
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

    vector<vector<int>> graph(vertices);

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected graph
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    parallelDFS(graph, start, vertices);

    return 0;
}