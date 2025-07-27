#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        cin >> dis[0][i], dis[i][0] = dis[0][i]; // 处理输入时确保对称性
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> dis[i][j];
    vector<int> dis_now = dis[0];
    vector<int> vis(n + 1);
    vis[0] = 1;
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int mn = INF, id = 1;
        for (int j = 1; j <= n; ++j)
        {
            if (vis[j])
                continue;
            if (dis_now[j] < mn)
            {
                mn = dis_now[j];
                id = j;
            }
        }
        for (int j = 1; j <= n; ++j)
        {
            if (vis[j])
                continue;
            dis_now[j] = min(dis_now[j], dis[id][j]);
        }
        vis[id] = 1;
        ans += mn;
    }
    cout << ans << endl;
}