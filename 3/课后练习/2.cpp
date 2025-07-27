#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> cnt(26), mark(26);
    for (char c : s)
        ++cnt[c - 'a'], mark[c - 'a'] = 1;
    auto get_max = [&](const auto &cnt) 
    {
        int mx = 0;
        for (int i = 0; i < 26; ++i)
            if (mark[i])
                mx = max(mx, cnt[i]);
        return mx;
    };
    auto get_min = [&](const auto &cnt) 
    {
        int mn = INT_MAX;
        for (int i = 0; i < 26; ++i)
            if (mark[i])
                mn = min(mn, cnt[i]);
        return mn;
    };
    auto check = [&]() {
        return get_max(cnt) - get_min(cnt) <= k;
    };
    if (!check())
    {
        cout << "-1" << endl;
        return;
    }
    for (int i = 0; i < s.size(); ++i)
    {
        for (int j = 0; j < 26; ++j)
            if (mark[j] && cnt[j])
            {
                --cnt[j];
                if (check())
                {
                    cout << char('a' + j);
                    break;
                }
                ++cnt[j];
            }
    }
    cout << endl;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}