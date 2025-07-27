#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> Pr;
#define End(X) return cout << (X) << '\n', void()
bool Nai;
int rd()
{
    int res = 0, f = 1;
    char c;
    do
        (c = getchar()) == '-' && (f = -1);
    while (!isdigit(c));
    while (isdigit(c))
        res = (c ^ 48) + (res << 1) + (res << 3), c = getchar();
    return res * f;
}
namespace T
{
    void solve()
    {
        int n = rd(), k = rd();
        vector<vector<pair<int, int>>> E(n + 1);
        for (int i = 1; i <= k; ++i)
        {
            int op = rd(), u = rd(), v = rd();
            if (op == 1)
                E[u].emplace_back(v, 0), E[v].emplace_back(u, 0);
            else if (op == 2)
                E[u].emplace_back(v, 1);
            else if (op == 3)
                E[v].emplace_back(u, 0);
            else if (op == 4)
                E[v].emplace_back(u, 1);
            else if (op == 5)
                E[u].emplace_back(v, 0);
        }
        vector<int> dfn(n + 1), low(n + 1), blk(n + 1);
        vector<int> sz, instack(n + 1);
        stack<int> stk;
        int tot = 0;
        auto tarjan = [&](auto self, int u) -> void
        {
            dfn[u] = low[u] = ++tot;
            stk.push(u);
            instack[u] = 1;
            for (auto [v, w] : E[u])
            {
                if (!dfn[v])
                    self(self, v), low[u] = min(low[u], low[v]);
                else if (instack[v])
                    low[u] = min(low[u], dfn[v]);
            }
            if (dfn[u] == low[u])
            {
                int id = sz.size();
                sz.emplace_back();
                while (1)
                {
                    int v = stk.top();
                    stk.pop();
                    ++sz[id];
                    blk[v] = id;
                    instack[v] = 0;
                    if (v == u)
                        break;
                }
            }
        };
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                tarjan(tarjan, i);
        int m = sz.size();
        vector<vector<pair<int, int>>> G(m);
        vector<int> in(m);
        int flag = 0;
        for (int i = 1; i <= n; ++i)
            for (auto [v, w] : E[i])
                if (blk[i] ^ blk[v])
                    G[blk[i]].emplace_back(blk[v], w), ++in[blk[v]];
                else if (w == 1)
                    flag = 1;
        queue<int> Q;
        vector<int> dis(m, 1);
        for (int i = 0; i < m; ++i)
            if (!in[i])
                Q.push(i);
        ll ans = 0;
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            ans += 1ll * sz[u] * dis[u];
            for (auto [v, w] : G[u])
            {
                dis[v] = max(dis[v], dis[u] + w);
                if (!--in[v])
                    Q.push(v);
            }
        }
        if (flag)
            End(-1);
        cout << ans << '\n';
    }
}
bool Ri;
int main()
{
    // cout << (&Ri - &Nai) / 8.0 / 1024 / 1024 << '\n';
    // ios::sync_with_stdio(0);
    // int t; cin >> t; while(t--)
    T::solve();
}
