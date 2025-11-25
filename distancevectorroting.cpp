#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = 1e9;

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter adjacency matrix (use " << INF << " for no link):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    // Distance Vector tables
    vector<vector<int>> dist = cost;
    vector<vector<int>> nextHop(n, vector<int>(n));

    // Initialize nextHop
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) nextHop[i][j] = i;
            else if (cost[i][j] < INF) nextHop[i][j] = j;
            else nextHop[i][j] = -1;
        }
    }

    // Bellman-Ford style relaxation: n-1 iterations
    for (int k = 0; k < n - 1; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int v = 0; v < n; v++) {
                    if (dist[i][v] + dist[v][j] < dist[i][j]) {
                        dist[i][j] = dist[i][v] + dist[v][j];
                        nextHop[i][j] = nextHop[i][v];
                    }
                }
            }
        }
    }

    // Print Routing Tables
    for (int i = 0; i < n; i++) {
        cout << "\nRouting Table for Node " << i << ":\n";
        cout << "Destination\tNextHop\tCost\n";

        for (int j = 0; j < n; j++) {
            cout << j << "\t\t";

            if (nextHop[i][j] == -1)
                cout << "-\t";
            else
                cout << nextHop[i][j] << "\t";

            if (dist[i][j] >= INF)
                cout << "INF\n";
            else
                cout << dist[i][j] << "\n";
        }
    }

    return 0;
}
