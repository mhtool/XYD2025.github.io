#include <bits/stdc++.h>
using namespace std;

int main()
{
    using ll = long long;
    int n;
    ll d;
    cin >> n >> d;
    const int OFFSET = 2e6 + 1;
    const int M = 4e6 + 5;

    vector<int> x(n), y(n);
    vector<int> cnt_x(M);
    vector<int> cnt_y(M);

    ll sum_x = 0, sum_y = 0;

    for (int i = 0; i < n; ++i)
    {
        cin >> x[i] >> y[i];
        x[i] += OFFSET;
        y[i] += OFFSET;

        sum_x += x[i];
        sum_y += y[i];

        ++cnt_x[x[i]];
        ++cnt_y[y[i]];
    }

    auto calc = [&](ll sum, const vector<int> &cnts, int l, int r) -> vector<ll>
    {
        vector<ll> ans(d + 1, 0);
        int start = l - d - 1;
        ll last = sum - 1ll * n * start;
        // (x_1 - x_start) + (x_2 - x_start) + ... + (x_n - x_start)    
        ll num = 0;
        for (int i = l - d; i <= r + d; ++i)
        {
            // 坐标为 i 时， \sum{|pos_j - i|} 的值
            ll now = last + num - (n - num);
            num += cnts[i];
            if (now <= d)
                ++ans[now];
            last = now;
        }
        return ans;
    };

    int min_x = *min_element(x.begin(), x.end());
    int max_x = *max_element(x.begin(), x.end());
    int min_y = *min_element(y.begin(), y.end());
    int max_y = *max_element(y.begin(), y.end());

    vector<ll> ans_x = calc(sum_x, cnt_x, min_x, max_x);
    vector<ll> ans_y = calc(sum_y, cnt_y, min_y, max_y);

    for (int i = 1; i <= d; ++i)
        ans_y[i] += ans_y[i - 1];

    ll ans = 0;
    for (int i = 0; i <= d; ++i)
        ans += ans_x[i] * ans_y[d - i];
    cout << ans << endl;

    return 0;
}