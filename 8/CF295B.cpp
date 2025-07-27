#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> dis[i][j];
    vector<long long> ans;
    vector<int> del(n + 1), has;
    for (int i = 1; i <= n; ++i)
        cin >> del[i];
    for (int k = n; k >= 1; --k)
    {
        int x = del[k];
        for (int u : has)
            for (int v : has)
                dis[u][v] = min(dis[u][v], dis[u][x] + dis[x][v]);
        long long res = 0;
        for (int u : has)
            for (int v : has)
                res += dis[u][v];
        ans.push_back(res);
    }
    reverse(ans.begin(), ans.end());
    for (auto x : ans)
        cout << x << " ";
    cout << "\n";
}