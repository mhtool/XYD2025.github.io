#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 定义无穷大
const int INF = 1e9;

// 为了在优先队列中存储 {权重, 顶点}
using Edge = pair<int, int>;

int main()
{
    int n;
    cin >> n;

    // 邻接矩阵存储图
    vector<vector<int>> adj(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> adj[i][j];

    // 优先队列优化 Prim 算法
    // 默认是最大堆，所以用 greater<Edge> 使其变为最小堆
    // 存储的 pair 是 {权重, 顶点编号}
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    vector<bool> vis(n + 1, false); // vis[i] 标记顶点i是否已加入MST
    long long ans_val = 0;          // 使用 long long 防止权重和溢出
    int ans_cnt = 0;                // 记录非零权重的边数

    // 从顶点1开始
    // 将 {权重0, 顶点1} 加入队列。
    // 权重0表示将顶点1加入生成树的代价是0
    pq.push({0, 1});

    // m log m Kruskal
    // m = n^2
    // n ^ 2
    while (!pq.empty())
    {
        // 1. 取出当前连接到MST代价最小的边 {权重, 顶点}
        auto [weight, u] = pq.top();
        pq.pop();

        // 2. 如果顶点u已经访问过，则跳过
        // 这是因为队列中可能存在连接到同一顶点的多条边，我们只选第一条（也就是最短的）
        if (vis[u])
            continue;

        // 3. 标记u为已访问，并累加结果
        vis[u] = true;
        ans_val += weight;
        if (weight != 0)
            ans_cnt++;

        // 4. 遍历u的所有邻居v
        for (int v = 1; v <= n; ++v)
            // 如果v未被访问过，将其连接到u的边加入优先队列
            if (!vis[v])
                pq.push({adj[u][v], v});
    }

    cout << ans_cnt << endl
         << ans_val << endl;

    return 0;
}