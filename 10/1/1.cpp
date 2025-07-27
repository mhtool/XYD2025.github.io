#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> dis[i][j];
    vector<int> dis_now = dis[1];
    vector<int> vis(n + 1);
    vis[1] = 1;
    int ans_val = 0, ans_cnt = 0;
    for (int i = 2; i <= n; ++i)
    {
        int mn = INF, id = -1;
        for (int j = 1; j <= n; ++j)
        {
            if (vis[j])
                continue;
            // 未选取的点击
            
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
        ans_val += mn;
        if (mn != 0)
            ++ans_cnt;
        vis[id] = 1;
    }
    cout << ans_cnt << endl
         << ans_val << endl;
}