
### **第一部分：基础概念 - 深度优先搜索的语言**

要理解 Tarjan，我们必须先对深度优先搜索 (DFS) 形成一个结构化的认识。当我们在图上进行 DFS 时，我们走过的路径会隐式地构成一棵**深度优先搜索树 (DFS Tree)**。

#### **1. 边的分类**
根据一个节点 `v` 相对于当前节点 `u` 在 DFS 树中的状态，我们可以将图中的边 `(u, v)` 分为四类：

*   **树边 (Tree Edge)**：在 DFS 中，`v` 尚未被访问，从 `u` 访问 `v` 的这条边 `(u, v)` 就是树边。所有树边共同构成了 DFS 树。
*   **返祖边 / 后向边 (Back Edge)**：`v` 已经被访问，并且 `v` 是 `u` 在 DFS 树中的祖先节点。**返祖边是构成环路的核心**。
*   **前向边 (Forward Edge)**：`v` 已经被访问，并且 `v` 是 `u` 在 DFS 树中的子孙节点。
*   **横叉边 (Cross Edge)**：`v` 已经被访问，但 `v` 既不是 `u` 的祖先，也不是 `u` 的子孙。它连接的是 DFS 树中两个不直接相关的分支。


#### **2. 连通性的定义**
*   **连通分量 (Connected Component)**：在**无向图**中，一个极大的连通子图。
*   **强连通分量 (Strongly Connected Component, SCC)**：在**有向图**中，一个极大的强连通子图。在其中，任意两点 u, v 之间双向可达。
*   **边双连通分量 (Edge-Biconnected Component, e-BCC)**：在无向图中，一个不包含**桥**的极大子图。任意两点间至少存在两条**边不重复**的路径。
*   **点双连通分量 (Vertex-Biconnected Component, v-BCC)**：在无向图中，一个不包含**割点**的极大子图。任意两点间至少存在两条**点不重复**的路径。

---

### **第二部分：有向图中的 Tarjan - 强连通分量 (SCC)**

现在我们正式进入 Tarjan 算法的核心。

#### **1. 核心组件**

Tarjan 算法在 DFS 基础上，引入了三个关键组件：
1.  **`dfn[u]` (Discovery Time)**：时间戳。记录节点 `u` 被首次访问的顺序。
2.  **`low[u]` (Lowest Reachable Ancestor's DFN)**：追溯值。记录从 `u` 出发，通过**零或多条树边**和**至多一条返祖边**，能到达的**最早的祖先节点**的 `dfn` 值。
3.  **一个栈 `S`**：存储当前搜索路径上的节点。这些节点是构成未来某个 SCC 的“候选成员”。

#### **2. `low` 值的计算逻辑（算法灵魂）**
在 DFS 到节点 `u` 时：
1.  **初始化**: `dfn[u] = low[u] = ++timestamp`。将 `u` 压入栈 `S`。
2.  **遍历 `u` 的邻居 `v`**:
    *   **情况一：`v` 是树边节点** (即 `v` 未被访问)
        *   **操作**：先递归 `tarjan(v)`，回溯后，执行 `low[u] = min(low[u], low[v])`。
        *   **逻辑**：`u` 可以到达 `v`，而 `v` 能追溯到的最早祖先，`u` 当然也能到达。`u` 继承了子树 `v` 的追溯能力。
    *   **情况二：`v` 是返祖边节点** (即 `v` 已被访问且在栈中)
        *   **操作**：执行 `low[u] = min(low[u], dfn[v])`。
        *   **逻辑**：我们从 `u` 找到了一条直达祖先 `v` 的返祖边。根据 `low` 值定义（至多一条返祖边），我们不能再利用 `v` 去跳得更远，只能用 `v` 自身的 `dfn` 值来更新。
    *   **情况三：`v` 是横叉边或前向边节点** (即 `v` 已被访问但已出栈)
        *   **操作**：忽略。
        *   **逻辑**：`v` 已属于一个被完全确定的 SCC。它无法帮助 `u` 追溯到当前路径上的任何祖先。

#### **3. SCC 的判定与提取**
当 `u` 的所有子树都访问完毕，准备回溯时，检查：
*   **判定条件：`dfn[u] == low[u]`**
*   **逻辑**：这个条件成立意味着，节点 `u` 及其所有子孙，无法通过任何返祖边到达比 `u` 更早的祖先。因此，`u` 是它所在 SCC 中，第一个被发现的节点，即“根”。
*   **提取**：此时，栈 `S` 中从栈顶到 `u` 的所有节点，共同构成一个完整的 SCC。将它们全部弹出。

---

### **第三部分：解题思路 - 为什么是 Tarjan？**

这是本次讲座的重点。**缩点是为了更好的递推吗？是的，这正是其核心目的。**

#### **1. 识别“缩点”信号**
在做题时，看到以下特征组合，你的“Tarjan 警报”就应该响起：
1.  **模型是有向图，且可能存在环。**
2.  **题目允许点/边被重复经过。**
3.  **关键信息/价值可以“打包”处理。**

以你提供的题目为例：
> “求一条路径，使路径经过的点权值之和最大。允许多次经过一个点，但是，重复经过的点，权值只计算一次。”

*   **分析**：
    *   “允许多次经过” -> 可以在图中自由移动。
    *   “权值只计算一次” -> 一旦进入一个区域，就可以把该区域所有点的价值一网打尽，且不会重复计算。
    *   **结论**：这个“区域”就是强连通分量 (SCC)。只要路径到达了一个 SCC，我们就可以通过在内部来回走动，获得这个 SCC 内所有节点的总权值。

#### **2. “缩点”：从复杂到简单的降维打击**
上述分析引导我们形成核心思路：**缩点 (Contraction)**。

*   **是什么**：将每个 SCC 看作一个单一的“超级节点”。新节点的权值是其内部所有原始节点权值之和。
*   **为什么**：
    1.  **简化结构**：SCC 内部复杂的环状结构被“打包”隐藏了。我们不再关心内部如何走，只关心这个“包”的总价值。
    2.  **破环成 DAG**：缩点后的新图，必然是一个**有向无环图 (DAG)**。这为后续的算法铺平了道路。
    3.  **启用新算法**：原图带环，无法直接拓扑排序或进行常规 DP。在新得到的 DAG 上，问题转化为了我们熟悉的 **DAG 最长路问题**，可以使用“拓扑排序 + DP” 在线性时间内解决。

**思考流程总结：**
`发现题目允许重复经过且价值可打包` -> `意识到 SCC 可视为整体` -> `构思“缩点”策略` -> `新问题是 DAG 上的 DP` -> `确定使用 Tarjan 算法作为实现“缩点”的工具`。

---

### **第四部分：无向图的 Tarjan - 桥与割点**

Tarjan 算法的思想同样适用于无向图，用于分析其“弱点”。

#### **1. 桥 (Bridge / Cut Edge)**
*   **定义**：删除后会增加图连通分量数量的**边**。
*   **判定法则**：对于树边 `(u, v)` (`u`是`v`的父节点)，它为桥的充要条件是 **`low[v] > dfn[u]`**。
*   **逻辑**：`v` 子树能追溯到的最早祖先，仍然在 `u` 的下方。这意味着 `v` 子树没有任何其它的返祖边能连接到 `u` 或 `u` 的上方。`(u, v)` 是其唯一通道。

#### **2. 割点 (Articulation Point / Cut Vertex)**
*   **定义**：删除后会增加图连通分量数量的**点**。
*   **判定法则**：
    1.  **根节点**：若 DFS 树的根 `u` 有两个或以上子树，则为割点。
    2.  **非根节点**：若存在子节点 `v`，满足 **`low[v] >= dfn[u]`**，则 `u` 为割点。
*   **逻辑**：`v` 子树能追溯到的最早祖先最多是 `u`，无法绕过 `u`。因此 `u` 是 `v` 子树与外界联系的唯一枢纽。

#### **3. 模板代码：SCC 与缩点 + DAG最长路**

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

// === Tarjan 算法求 SCC ===
vector<int> adj[100005];
int dfn[100005], low[100005], timestamp;
stack<int> s;
bool in_stack[100005];
int scc_id[100005], scc_count;
long long scc_val[100005]; // 每个 SCC 的总权值

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    s.push(u);
    in_stack[u] = true;

    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        ++scc_count;
        int top;
        do {
            top = s.top(); s.pop();
            in_stack[top] = false;
            scc_id[top] = scc_count; // 为每个弹出的节点分配 SCC 编号
        } while (top != u);
    }
}

// === 缩点后在 DAG 上求最长路 ===
vector<int> new_adj[100005];
int in_degree[100005];
long long dp[100005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // 1. 执行 Tarjan 算法
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    // 2. 缩点: 计算新点权值，构建新图
    for (int i = 1; i <= n; ++i) {
        scc_val[scc_id[i]] += a[i];
        for (int v : adj[i]) {
            if (scc_id[i] != scc_id[v]) {
                new_adj[scc_id[i]].push_back(scc_id[v]);
                in_degree[scc_id[v]]++;
            }
        }
    }

    // 去除新图中的重边 (可选，但好习惯)
    for (int i = 1; i <= scc_count; ++i) {
        sort(new_adj[i].begin(), new_adj[i].end());
        new_adj[i].erase(unique(new_adj[i].begin(), new_adj[i].end()), new_adj[i].end());
    }

    // 3. 拓扑排序 + DP 求最长路
    queue<int> q;
    for (int i = 1; i <= scc_count; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
        dp[i] = scc_val[i];
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : new_adj[u]) {
            dp[v] = max(dp[v], dp[u] + scc_val[v]);
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 4. 统计答案
    long long ans = 0;
    for (int i = 1; i <= scc_count; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;

    return 0;
}
```

---

### **总结**

Tarjan 算法系列并非孤立的模板，而是一种基于 DFS 的、深刻的图结构分析方法。
*   它通过 `dfn` 和 `low` 数组，精妙地捕捉了“树”与“环”的相互作用。
*   在解题中，它是一种**降维工具**，能将复杂的带环图转化为易于处理的 DAG，从而为动态规划等更高层算法的使用创造条件。

希望通过今天的讲解，大家不仅学会了 Tarjan 算法的实现，更能理解其应用场景，在未来的比赛中，能敏锐地识别出那些需要它来“化繁为简”的问题。

谢谢大家！