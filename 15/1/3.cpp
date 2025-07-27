#include <bits/stdc++.h>
using namespace std;

struct StringHash
{
    static const int P = 233;
    static const int mod = 1e9 + 7;
    int n;
    vector<int> pw;
    vector<int> hash;
    StringHash(string s)
    {
        n = s.size();
        s = " " + s;
        hash.resize(n + 1);
        pw.resize(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            hash[i] = (1ll * hash[i - 1] * P + s[i]) % mod;
            pw[i] = 1ll * pw[i - 1] * P % mod;
        }
    }
    int get_hash(int l, int r)
    {
        return (hash[r] - 1ll * hash[l - 1] * pw[r - l + 1] % mod + mod) % mod;
    }
};
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    StringHash sh(s);
    StringHash rh(string(s.rbegin(), s.rend()));
    auto check_palindrome = [&](int l, int r)
    {
        return sh.get_hash(l, r) == rh.get_hash(n - r + 1, n - l + 1);
    };
    vector<int> dp(n + 1);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (check_palindrome(1, i))
            dp[i] = dp[i / 2] + 1;
        ans += dp[i];
    }
    cout << ans << endl;
}