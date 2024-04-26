#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void parallel_bfs(vector<vector<int> >& graph, int start_node) {
    int num_nodes = graph.size();
    vector<bool> visited(num_nodes, false);
    visited[start_node] = true;
    queue<int> q;
    q.push(start_node);

    while (!q.empty()) {
        int current;
        #pragma omp parallel shared(q, visited) private(current)
        {
            #pragma omp critical
            {
                current = q.front();
                q.pop();
            }

            // Print the current node being visited
            cout << "Visiting Node: " << current << endl;

            #pragma omp for
            for (int i = 0; i < graph[current].size(); ++i) {
                int neighbor = graph[current][i];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}


int main() {
    int num_nodes;
    cout << "Enter the number of nodes: ";
    cin >> num_nodes;

    vector<vector<int> > graph(num_nodes);

    cout << "Enter the adjacency list for each node (enter -1 to stop):\n";
    for (int i = 0; i < num_nodes; ++i) {
        cout << "Node " << i << ": ";
        int neighbor;
        while (cin >> neighbor && neighbor != -1) {
            graph[i].push_back(neighbor);
        }
    }

    int start_node;
    cout << "Enter the starting node for BFS: ";
    cin >> start_node;

    parallel_bfs(graph, start_node);

    return 0;
}
