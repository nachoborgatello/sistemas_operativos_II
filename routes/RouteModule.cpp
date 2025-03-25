#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

typedef pair<int, int> pii; // (distancia, nodo)

vector<int> dijkstra(int n, vector<vector<pii>>& adj, int source) {
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        
        for (auto [weight, v] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

void addEdge(vector<vector<pii>>& adj, int u, int v, int weight) {
    adj[u].push_back({weight, v});
    adj[v].push_back({weight, u}); // Grafo no dirigido
}

int main() {
    int n = 5;
    vector<vector<pii>> adj(n);
    
    addEdge(adj, 0, 1, 10);
    addEdge(adj, 0, 2, 3);
    addEdge(adj, 1, 2, 1);
    addEdge(adj, 1, 3, 2);
    addEdge(adj, 2, 3, 4);
    addEdge(adj, 2, 4, 8);
    addEdge(adj, 3, 4, 7);
    
    vector<int> distances = dijkstra(n, adj, 0);
    
    for (int i = 0; i < n; i++)
        cout << "Nodo " << i << ": " << (distances[i] == INF ? -1 : distances[i]) << "\n";
    
    return 0;
}
