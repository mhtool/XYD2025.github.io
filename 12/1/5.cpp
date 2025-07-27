#include <bits/stdc++.h>
using namespace std;

int main()
{
    const int mod = 1e9 + 7;
    int R, C, minT, maxT;
    cin >> R >> C >> minT >> maxT;

    auto get_ans = [&](int limit)
    {
        vector<int> ans(maxT + 1);
        for (int d = 2; d < limit; ++d)
        {
            int dis = 2 * d;
            if (dis > maxT)
                break;
            int cnt = 1ll * (limit - d) * (d - 1) % mod;
            ans[dis] = (ans[dis] + cnt) % mod;
        }
        return ans;
    };

    auto ans_r = get_ans(R);
    auto ans_c = get_ans(C);

    for (int i = 1; i <= maxT; ++i)
    {
        ans_r[i] = (ans_r[i] + ans_r[i - 1]) % mod;
        ans_c[i] = (ans_c[i] + ans_c[i - 1]) % mod;
    }

    auto get_sum = [&](const auto &ans, int l, int r)
    {
        if (r < l)
            return 0;
        if (l == 0)
            return ans[r];
        return (ans[r] - ans[l - 1] + mod) % mod;
    };

    int ans = 0;

    for (int i = 0; i <= minT; ++i)
        ans = (ans + 1ll * get_sum(ans_r, i, i) * get_sum(ans_c, minT - i, maxT - i) % mod) % mod;

    for (int i = minT + 1; i <= maxT; ++i)
        ans = (ans + 1ll * get_sum(ans_r, i, i) * get_sum(ans_c, 0, maxT - i) % mod) % mod;
    cout << (1ll * ans * 6) % mod << endl;
}