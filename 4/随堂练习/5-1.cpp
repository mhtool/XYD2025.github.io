#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    const int use[] = {0, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    cin >> n >> m;
    vector<int> a(m);
    vector<string> dp(n + 1, "?");
    for (int &x : a)
        cin >> x;
    dp[0] = "";
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (i - use[a[j]] < 0)
                continue;
            if (dp[i - use[a[j]]] == "?")
                continue;
            if (dp[i] == "?")
                dp[i] = dp[i - use[a[j]]] + char(a[j] + '0');
            else
                dp[i] = max(dp[i], dp[i - use[a[j]]] + to_string(a[j]),
                 [](const string &a, const string &b)
                { return a.size() < b.size() || (a.size() == b.size() && a < b); });
    }
    cout << dp[n] << endl;
}