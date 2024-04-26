#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void parallel_dfs(vector<vector<int> >& graph, int start_node) {
    int num_nodes = graph.size();
    vector<bool> visited(num_nodes, false);
    stack<int> s;
    s.push(start_node);

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (!visited[current]) {
            visited[current] = true;
            cout << "Visiting Node: " << current << endl;

            for (int i = 0; i < graph[current].size(); ++i) {
                int neighbor = graph[current][i];
                if (!visited[neighbor]) {
                    s.push(neighbor);
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
    cout << "Enter the starting node for DFS: ";
    cin >> start_node;

    parallel_dfs(graph, start_node);

    return 0;
}
