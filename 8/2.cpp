#include <bits/stdc++.h>
using namespace std;
int main()
{

    const int mod = 100003;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edge(n + 1);

    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    queue<int> q;
    q.push(1);
    vector<int> dis(n + 1, -1);
    vector<int> ans(n + 1, 0);
    ans[1] = 1;
    dis[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : edge[u])
        {
            if (dis[v] == -1)
            {
                dis[v] = dis[u] + 1;
                q.push(v);
                ans[v] = ans[u];
            }
            else if (dis[v] == dis[u] + 1)
            {
                ans[v] = (ans[v] + ans[u]) % mod;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << endl;
}