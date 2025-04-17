#include <iostream>
using namespace std;

const int MAX_NODES = 6; // Number of tasks (A, B, C, D, E, F)
int graph[MAX_NODES][MAX_NODES] = {0};  // Adjacency matrix
int indegree[MAX_NODES] = {0};          // Indegree array
int result[MAX_NODES];                  // Stores topological order

void topologicalSort(int nodes) {
    int queue[MAX_NODES];
    int front = 0, back = 0;
    int resultIndex = 0;

    // Initialize queue with nodes having indegree = 0
    for (int i = 0; i < nodes; i++) {
        if (indegree[i] == 0) {
            queue[back++] = i;
        }
    }

    while (front < back) {
        int u = queue[front++];
        result[resultIndex++] = u;

        // For each neighbor v of u
        for (int v = 0; v < nodes; v++) {
            if (graph[u][v] == 1) {   // Edge exists
                indegree[v]--;        // Decrement indegree of v
                if (indegree[v] == 0) {
                    queue[back++] = v;
                }
            }
        }
    }

    // Check if there was a cycle
    if (resultIndex != nodes) {
        cout << "Graph has a cycle, topological sorting not possible." << endl;
    } else {
        cout << "Topological Order: ";
        for (int i = 0; i < resultIndex; i++) {
            cout << char(result[i] + 'A') << " ";  // Convert index to character
        }
        cout << endl;
    }
}

int main() {
    int nodes = MAX_NODES;

    // Define dependencies in the adjacency matrix
    graph[0][1] = 1; // A → B
    graph[0][2] = 1; // A → C
    graph[1][3] = 1; // B → D
    graph[2][3] = 1; // C → D
    graph[3][4] = 1; // D → E
    graph[5][2] = 1; // F → C

    // Initialize indegrees based on the dependencies
    for (int u = 0; u < nodes; u++) {
        for (int v = 0; v < nodes; v++) {
            if (graph[u][v] == 1) {
                indegree[v]++;
            }
        }
    }

    // Perform topological sort and output the result
    topologicalSort(nodes);

    return 0;
}