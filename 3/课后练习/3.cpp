#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int k;
    string s;
    cin >> s >> k;
    int n = s.size(), m = n - k;
    string ans; // vector
    for (int i = 0; i < n; ++i)
    {
        if (n - i >= m && !ans.empty() && ans.front() > s[i] && s[i] != '0')
            ans.clear();
        while (1)
        {
            if (ans.empty())
                break;
            bool flag = false;
            flag |= ans.size() == 1 && s[i] == '0';
            flag |= ans.size() + (n - i) <= m;
            flag |= ans.back() <= s[i];
            if (flag)
                break;
            ans.pop_back();
        }
        if (ans.size() < m)
            ans.push_back(s[i]);
    }
    cout << ans << '\n';
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}