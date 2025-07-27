#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, v, k;
    cin >> n >> v >> k;
    
    vector<int> val(n), vol(n);
    for (int i = 0; i < n; ++i)
        cin >> val[i];
    for (int i = 0; i < n; ++i)
        cin >> vol[i];
    
    vector<vector<int>> dp(v + 1, vector<int>(k));
    for (int i = 0; i < n; ++i)
    {
        for (int j = v; j >= vol[i]; --j)
        {   
            vector<int> res;
            for (int l = 0; l < k; ++l)
            {
                res.push_back(dp[j][l]);
                res.push_back(dp[j - vol[i]][l] + val[i]);
            }
            sort(res.begin(), res.end(), greater<int>());
            res.erase(unique(res.begin(), res.end()), res.end());
            for (int l = 0; l < k && l < res.size(); ++l)
                dp[j][l] = res[l]; 
        }
    }
    
    cout << dp[v][k - 1] << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}