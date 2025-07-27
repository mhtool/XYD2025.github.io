#include <bits/stdc++.h>
using namespace std;

// 定义 Edge 类型别名
using Edge = array<int, 3>;
using Edge2 = pair<int, int>;

// --- 全局变量声明 ---
// 图的属性
int n, m;
vector<Edge> edges;

// 并查集 & Kruskal 重构树
vector<int> fa;                     // 并查集的父节点数组 & 重构树节点的父节点
vector<vector<Edge2>> edge_kruskal; // 最小生成树的图

// LCA (最近公共祖先)
vector<vector<int>> fa_k; // 祖先数组 (用于倍增)
vector<vector<int>> val;        // 生成树中节点的权值，代表到上方节点的路径权值
vector<int> dep;                // 节点的深度

// --- 功能函数 ---

// 1. 并查集查找操作 (路径压缩)
int find(int x)
{
    while (fa[x] != x)
        x = fa[x] = fa[fa[x]];
    return x;
}

// 2. 读取输入数据
void read_input()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
}

// 3. 构建最小生成树
void build_kruskal_tree()
{
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0); // 初始化并查集
    edge_kruskal.resize(n + 1);

    sort(edges.begin(), edges.end());

    for (auto [w, u, v] : edges)
    {
        int fu = find(u);
        int fv = find(v);

        if (fu != fv)
        {
            fa[fu] = fv; // 合并两个集合
            edge_kruskal[u].emplace_back(v, w);
            edge_kruskal[v].emplace_back(u, w);
        }
    }
}

// 4. LCA 预处理 (DFS)
void dfs(int u, int f)
{
    fa_k[u][0] = f;
    dep[u] = dep[f] + 1;
    for (int i = 1; i < 20; ++i)
    {
        fa_k[u][i] = fa_k[fa_k[u][i - 1]][i - 1];
        val[u][i] = max(val[u][i - 1], val[fa_k[u][i - 1]][i - 1]);
    }
    for (auto [v, w] : edge_kruskal[u])
        if (v != f)
        {
            val[v][0] = w; // 记录到父节点的权值
            dfs(v, u);
        }
}

// 5. LCA 查询
int get_ans(int u, int v)
{
    int ans = 0;
    // 确保 u 的深度更大
    if (dep[u] < dep[v])
        swap(u, v);

    // 将 u 跳到和 v 同样的深度
    for (int i = 19; i >= 0; --i)
        if (dep[fa_k[u][i]] >= dep[v])
        {
            ans = max(ans, val[u][i]);
            u = fa_k[u][i];
        }

    if (u == v)
        return ans;

    // u 和 v 一起向上跳，直到它们的父节点相同
    for (int i = 19; i >= 0; --i)
        if (fa_k[u][i] != fa_k[v][i])
        {
            ans = max(ans, val[u][i]);
            ans = max(ans, val[v][i]);

            u = fa_k[u][i];
            v = fa_k[v][i];
        }
    ans = max(ans, val[u][0]);
    ans = max(ans, val[v][0]);

    return ans;
}

// 6. 处理所有查询
void process_queries()
{
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        int ans = get_ans(u, v);
        cout << ans << endl;
    }
}

int main()
{
    // --- 主逻辑流程 ---
    read_input();
    build_kruskal_tree();

    // 预处理 LCA
    fa_k.assign(n + 1, vector<int>(20, 0));
    val.assign(n + 1, vector<int>(20, 0));
    dep.assign(n + 1, 0);
    dfs(1, 0);
    process_queries();

    return 0;
}