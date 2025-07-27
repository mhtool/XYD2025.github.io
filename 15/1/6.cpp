#include <bits/stdc++.h>
using namespace std;
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    vector<int> pi(n + 1);
    for (int i = 2; i <= n; ++i)
    {
        int len = pi[i - 1];
        while (len && s[i] != s[len + 1])
            len = pi[len];
        if (s[i] == s[len + 1])
            ++len;
        pi[i] = len;
    }

    vector<int> dep(n + 1);
    for (int i = 1; i <= n; ++i)
        dep[i] = dep[pi[i]] + 1;
    int ans = 1;
    const int mod = 1e9 + 7;
    vector<int> mid_pi(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int len = mid_pi[i - 1];
        while (len && s[i] != s[len + 1])
            len = pi[len];
        if (s[i] == s[len + 1])
            ++len;
        while (len > i / 2)
            len = pi[len];
        mid_pi[i] = len;
        ans = (1ll * ans * (dep[mid_pi[i]] + 1)) % mod;
    }
    cout << ans << endl;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}