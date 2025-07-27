#include <bits/stdc++.h>

// 采用您的代码风格偏好
using namespace std;
const int INF = 0x3f3f3f3f;
using ll = long long;

// 使用结构体从BFS中返回多个值，比元组更清晰
struct BFSResult 
{
    vector<int> dist;       // 从起点到各点的距离
    vector<int> max_weight; // 从起点到各点的路径上的最大边权
    vector<int> parent;     // 用于路径重建的父节点指针
};


int main()
{
    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<array<int, 3>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    }
    
    auto bfs = [&](int S) -> BFSResult 
    {
        vector<int> dist(n + 1, INF);
        vector<int> max_w(n + 1, 0);
        vector<int> parent(n + 1, -1);
        queue<int> q;
    
        dist[S] = 0;
        q.push(S);
    
        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();
            for (auto [v, w] : adj[u]) 
            {
    
                // 发现一条更短的路径
                if (dist[v] > dist[u] + 1) 
                {
                    dist[v] = dist[u] + 1;
                    max_w[v] = max(max_w[u], w);
                    parent[v] = u;
                    q.push(v);
                }
                // 发现一条等长的最短路径
                else if (dist[v] == dist[u] + 1) 
                {
                    // 通过选择有更大“最大边权”的路径来打破平局
                    if (max_w[v] < max(max_w[u], w)) 
                    {
                        max_w[v] = max(max_w[u], w);
                        parent[v] = u;
                    }
                }
            }
        }
        return BFSResult{dist, max_w, parent};
    };
    // 分别从起点（1）和终点（n）运行BFS
    auto from_start = bfs(1);
    auto from_end = bfs(n);

    // 根据题意寻找最优路径和“分割边”
    // 标准是：在从1到n的最短路径上找到一条边(u, v)，
    // 使得 abs(max(1到u的最大边权, n到v的最大边权) - uv的边权) 最大化
    int max_val = -1;
    pair<int, int> key_path;

    for (auto [u, v, w] : edges) {

        // 检查该边是否存在于某条1到n的最短路径上
        if (from_start.dist[u] + from_end.dist[v] + 1 == from_start.dist[n])
        {
            int mx = max(from_start.max_weight[u], from_end.max_weight[v]);
            int now = abs(mx - w);
            
            if (now >= max_val) 
            {
                max_val = now;
                key_path = {u, v};
            }
        }
    }
    
    // 使用两次BFS的父节点指针重构最终路径
    vector<int> path;
    auto [u, v] = key_path;

    // 第一部分：从起点(1)到u的路径
    int curr = u;
    vector<int> path_part1;
    while (curr != -1) 
    {
        path_part1.push_back(curr);
        curr = from_start.parent[curr];
    }

    reverse(path_part1.begin(), path_part1.end());
    path.insert(path.end(), path_part1.begin(), path_part1.end());

    // 第二部分：从v到终点(n)的路径
    curr = v;
    while (curr != -1) {
        path.push_back(curr);
        curr = from_end.parent[curr];
    }
    
    // 输出最短路径的长度（边数）和构成最优路径的节点
    cout << from_start.dist[n] << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << (i == path.size() - 1 ? "" : " ");
    }
    cout << endl;

}