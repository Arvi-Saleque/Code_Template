class ShortestPath {
public:
    vector<vector<pair<int, int>>> gr;
    vector<int> par;                   
    vector<long long> dis;             
    vector<bool> vis;                  
    void dijkstra(int source) {
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, source});
        dis[source] = 0;

        while (!pq.empty()) {
            auto node = pq.top();
            pq.pop();
            long long v_dist = node.first;
            int v = node.second;

            if (vis[v])
                continue;

            vis[v] = true;

            for (auto &child : gr[v]) {
                int child_v = child.first;
                int wt = child.second;

                if (dis[v] + wt < dis[child_v]) {
                    dis[child_v] = dis[v] + wt;
                    par[child_v] = v;
                    pq.push({dis[child_v], child_v});
                }
            }
        }
    }
    vector<int> getPath(int source, int dest) {
        vector<int> path;
        if (dis[dest] == LLONG_MAX) {
            return path; // No path found
        }
        for (int v = dest; v != -1; v = par[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void bellmanFord(int source) {
        dis[source] = 0;
        int n = gr.size() - 1;

        for (int i = 1; i <= n - 1; ++i) {
            for (int u = 1; u <= n; ++u) {
                for (auto &child : gr[u]) {
                    int v = child.first;
                    int w = child.second;
                    if (dis[u] != LLONG_MAX && dis[u] + w < dis[v]) {
                        dis[v] = dis[u] + w;
                        par[v] = u;
                    }
                }
            }
        }

        for (int u = 1; u <= n; ++u) {
            for (auto &child : gr[u]) {
                int v = child.first;
                int w = child.second;
                if (dis[u] != LLONG_MAX && dis[u] + w < dis[v]) {
                    cout << "Graph contains a negative weight cycle" << endl;
                    return;
                }
            }
        }
    }

    void floydWarshall(vector<vector<long long>> &dist) {
        int n = gr.size() - 1;
        dist.resize(n + 1, vector<long long>(n + 1, LLONG_MAX));

        for (int i = 1; i <= n; ++i) {
            dist[i][i] = 0;
        }

        for (int u = 1; u <= n; ++u) {
            for (auto &child : gr[u]) {
                int v = child.first;
                int w = child.second;
                dist[u][v] = w;
            }
        }

        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
};
