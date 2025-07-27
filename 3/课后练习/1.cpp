#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, c;
    cin >> n >> c;
    struct point
    {
        int val, id;
    };
    auto get_cost = [&](const point &a)
    {
        return min(a.val + a.id, a.val + n + 1 - a.id);
    };
    auto cmp = [&](const point &a, const point &b)
    {
        return get_cost(a) < get_cost(b);
    };
    vector<point> a(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a.begin() + 1, a.end(), cmp);
    vector<long long> sum(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + get_cost(a[i]);
        // pos[a[i].id] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int now = c - (a[i].val + a[i].id);
        if (now < 0)
            continue;
        now += get_cost(a[i]);
        int num = upper_bound(sum.begin() + 1, sum.end(), now) - sum.begin() - 1;
        if (num >= i)
            ans = max(ans, num);
        else
        {
            now -= get_cost(a[i]);
            num = upper_bound(sum.begin() + 1, sum.begin() + i, now) - sum.begin() - 1;
            ans = max(ans, num + 1);
        }
    }
    cout << ans << '\n';
    return;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}