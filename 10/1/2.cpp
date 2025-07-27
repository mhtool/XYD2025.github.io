#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>

using namespace std;

// 定义 Edge 类型别名
using Edge = array<int, 3>;

// --- 全局变量声明 ---
// 图的属性
int n, m;
vector<Edge> edges;

// 并查集 & Kruskal 重构树
int root;                         // 重构树的根节点
vector<int> fa;                   // 并查集的父节点数组 & 重构树节点的父节点
vector<vector<int>> edge_kruskal; // 重构树的邻接表
vector<int> val;                  // 重构树中非叶子节点的权值

// LCA (最近公共祖先)
vector<vector<int>> fa_kruskal; // 祖先数组 (用于倍增)
vector<int> dep;                // 节点的深度

// --- 功能函数 ---

// 1. 并查集查找操作 (路径压缩)
int find_set(int x)
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

// 3. 构建 Kruskal 重构树
void build_kruskal_tree()
{
    // 初始化变量
    // 节点总数最多为 n (原始) + n-1 (新建)
    int max_nodes = n * 2;
    fa.resize(max_nodes);
    iota(fa.begin(), fa.end(), 0); // 初始化并查集
    edge_kruskal.resize(max_nodes);
    val.resize(max_nodes);

    sort(edges.begin(), edges.end());

    int num = n; // 当前节点总数
    for (const auto &edge : edges)
    {
        int w = edge[0], u = edge[1], v = edge[2];
        int fu = find_set(u);
        int fv = find_set(v);

        if (fu != fv)
        {
            num++;
            fa[fu] = num;
            fa[fv] = num;
            edge_kruskal[num].push_back(fu);
            edge_kruskal[num].push_back(fv);
            val[num] = w;
        }
    }
    root = num; // 最后一个合并产生的节点即为根
}

// 4. LCA 预处理 (DFS)
void dfs_for_lca(int u, int f)
{
    fa_kruskal[u][0] = f;
    dep[u] = dep[f] + 1;
    for (int i = 1; i < 20; ++i)
    {
        fa_kruskal[u][i] = fa_kruskal[fa_kruskal[u][i - 1]][i - 1];
    }
    for (int v : edge_kruskal[u])
    {
        if (v != f)
        {
            dfs_for_lca(v, u);
        }
    }
}

// 5. LCA 查询
int get_lca(int u, int v)
{
    // 确保 u 的深度更大
    if (dep[u] < dep[v])
        swap(u, v);

    // 将 u 跳到和 v 同样的深度
    for (int i = 19; i >= 0; --i)
        if (dep[fa_kruskal[u][i]] >= dep[v])
            u = fa_kruskal[u][i];

    if (u == v)
    {
        return u;
    }

    // u 和 v 一起向上跳，直到它们的父节点相同
    for (int i = 19; i >= 0; --i)
    {
        if (fa_kruskal[u][i] != fa_kruskal[v][i])
        {
            u = fa_kruskal[u][i];
            v = fa_kruskal[v][i];
        }
    }
    return fa_kruskal[u][0];
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
        int lca = get_lca(u, v);
        cout << val[lca] << endl;
    }
}

int main()
{
    // 提高 IO 效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // --- 主逻辑流程 ---
    read_input();
    build_kruskal_tree();

    // 预处理 LCA
    int max_nodes = n * 2;
    fa_kruskal.assign(max_nodes, vector<int>(20, 0));
    dep.assign(max_nodes, 0);
    dfs_for_lca(root, 0); // 从根节点开始 DFS

    process_queries();

    return 0;
}