#include <bits/stdc++.h>
using namespace std;

void kmp_1_index(string s, string t)
{
    string str = " " + s + '#' + t;
    int n = s.size(), m = t.size();
    int tot = n + m + 2;
    vector<int> pi(tot);
    int ans = 0;
    
    for (int i = 2; i < tot; ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && str[len + 1] != str[i])
            len = pi[len];
        if (str[len + 1] == str[i])
            // pi[i] = len + 1;
        ++len;
        pi[i] = len;
        cout << pi[i] << " ";
    }
    cout << endl;

    vector<int> dp(m + 2);
    for (int i = m - n + 1; i >= 1; --i)
    {
        dp[i] = max(dp[i], dp[i + 1]);
        if (pi[i + n + n] == n)
            dp[i] = max(dp[i], dp[i + n] + 1);
    }
    // for (int i = 1; i <= m; ++i)
    //     cout << dp[i] << " ";
    // cout << "\n";
    cout << dp[1] << endl;
}
int main()
{
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    kmp_1_index(t, s);
}