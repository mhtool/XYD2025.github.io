#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

int main()
{

    int n;
    cin >> n;
    using status = bitset<155>;
    vector<vector<int>> edge(n + 1);
    auto dp = vector(n + 1, vector<status>(n + 1));
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    vector<int> sz(n + 1);

    auto dfs_sz = [&](auto &&self, int u, int f) -> void
    {
        sz[u] = 1;
        for (int v : edge[u])
        {
            if (v == f)
                continue;
            self(self, v, u);
            sz[u] += sz[v];
        }
    };
    auto dfs_ans = [&](auto &&self, int u, int f, int sum) -> void
    {
        
    };

    dfs_sz(dfs_sz, 1, 0);

    return 0;
}