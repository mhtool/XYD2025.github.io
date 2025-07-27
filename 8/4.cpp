#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge& other) const
    {
        return w < other.w;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    // 按边权排序
    sort(edges.begin(), edges.end());
    
    // 取出前k短的边，收集涉及的节点
    set<int> nodes;
    for (int i = 0; i < k; i++)
    {
        nodes.insert(edges[i].u);
        nodes.insert(edges[i].v);
    }
    
    // 将节点重新编号
    vector<int> node_list(nodes.begin(), nodes.end());
    map<int, int> node_map;
    for (int i = 0; i < node_list.size(); i++)
        node_map[node_list[i]] = i;
    
    int sub_n = node_list.size();
    
    // 在子图上建立距离矩阵
    vector<vector<long long>> dis(sub_n, vector<long long>(sub_n, 1e18));
    
    // 初始化对角线为0
    for (int i = 0; i < sub_n; i++)
        dis[i][i] = 0;
    
    // 添加前k短的边
    for (int i = 0; i < k; i++)
    {
        int u = node_map[edges[i].u];
        int v = node_map[edges[i].v];
        long long w = edges[i].w;
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
    
    // Floyd算法计算最短路径
    for (int k = 0; k < sub_n; k++)
        for (int i = 0; i < sub_n; i++)
            for (int j = 0; j < sub_n; j++)
                if (dis[i][k] != 1e18 && dis[k][j] != 1e18)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    
    // 收集所有点对之间的最短路径
    vector<long long> paths;
    for (int i = 0; i < sub_n; i++)
        for (int j = i + 1; j < sub_n; j++)
            if (dis[i][j] != 1e18)
                paths.push_back(dis[i][j]);
    
    // 排序
    sort(paths.begin(), paths.end());
    
    // 输出第k长的路径
    cout << paths[k - 1] << endl;
    
    return 0;
}
