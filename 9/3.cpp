#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> fa(n + 1);
    iota(fa.begin(), fa.end(), 0);
    auto find = [&](int u) -> int
    {
        while (u != fa[u])
            u = fa[u] = fa[fa[u]];
        return u;
    };
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        int fu = find(u);
        int fv = find(v);
        if (fu != fv)
            fa[fu] = fv;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (find(i) == i)
            ++ans;
    cout << ans << '\n';
}