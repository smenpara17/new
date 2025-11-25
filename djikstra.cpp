#include <bits/stdc++.h>
using namespace std;

void printPath(int node, vector<int>& parent) {
    vector<int> path;
    while (node != -1) {
        path.push_back(node);
        node = parent[node];
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
}

void dijkstra(int src, vector<vector<pair<int,int>>>& adj, int n) {
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<int> nextHop(n, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;

                // Determine next hop
                nextHop[v] = (u == src ? v : nextHop[u]);

                pq.push({dist[v], v});
            }
        }
    }

    // Routing table (OSPF)
    cout << "\n=== OSPF Routing Table for Router " << src << " ===\n";
    cout << "Destination\tNext Hop\tCost\n";
    for (int i = 0; i < n; i++) {
        cout << i << "\t\t";
        if (i == src) cout << "-\t\t";
        else cout << nextHop[i] << "\t\t";
        cout << dist[i] << endl;
    }

    // Full path printing
    cout << "\n=== Full Shortest Paths from Router " << src << " ===\n";
    for (int i = 0; i < n; i++) {
        cout << "Path to " << i << " (Cost: " << dist[i] << "): ";
        printPath(i, parent);
        cout << "\n";
    }
}

int main() {
    int n, e;
    cout << "Enter number of routers and links: ";
    cin >> n >> e;

    vector<vector<pair<int,int>>> adj(n);

    cout << "Enter links as: u v cost\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src;
    cout << "Enter source router: ";
    cin >> src;

    dijkstra(src, adj, n);

    return 0;
}
