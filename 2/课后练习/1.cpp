#include <bits/stdc++.h>
using namespace std;
#define int long long
main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, p, c;
    cin >> n >> p >> c;
    if (c >= p)
    {
        cout << 0 << '\n';
        return 0;
    }
    auto Qpow = [&](int x, int p, int mod)
    {
        int res = 1;
        while (p)
        {
            if (p & 1)
                res = (1ll * res * x) % mod;
            x = (1ll * x * x) % mod;
            p >>= 1;
        }
        return res;
    };
    auto get_inv = [&](int x, int mod)
    {
        return Qpow(x, mod - 2, mod);
    };
    vector<int> a(n);
    for (int &x : a)
        cin >> x, x %= p;
    int mid = n / 2;
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    auto get_ans = [&](const vector<int> &arr)
    {
        int n = arr.size();
        int m = 1 << n;
        map<int, int> ans_map;
        for (int i = 0; i < m; ++i)
        {
            int now = 1;
            for (int j = 0; j < n; ++j)
                if (i & (1 << j))
                    now = (1ll * now * arr[j]) % p;
            ++ans_map[now];
        }
        return ans_map;
    };
    auto left_map = get_ans(left);
    auto right_map = get_ans(right);
    const int mod = 1e9 + 7;
    int ans = 0;
    if (c == 0)
    {
        int cntl = 0;
        int cntr = 0;
        for (auto [val, cnt] : left_map)
            cntl = (cntl + cnt) % mod;
        for (auto [val, cnt] : right_map)
            cntr = (cntr + cnt) % mod;
        ans = (left_map[0] * cntr % mod + right_map[0] * cntl % mod - left_map[0] * right_map[0] % mod + mod) % mod;
        cout << ans << '\n';
        return 0;
    }
    for (auto [val, cnt] : left_map)
    {
        int target = (1ll * c * get_inv(val, p)) % p;
        ans = (ans + 1ll * cnt * right_map[target] % mod) % mod;
    }
    if (c == 1)
        ans = (ans + mod - 1) % mod; // Ensure non-negative result
    cout << ans << '\n';
    return 0;
}