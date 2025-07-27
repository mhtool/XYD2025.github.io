#include <bits/stdc++.h>
using namespace std;
int main()
{
    typedef long long ll;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    int l = 0, r = 2 * a.back(), ans = 0;
    auto check = [&](int x) -> bool
    {
        ll cnt = 0;
        for (int i = 0, j = n - 1; i < j; ++i)
        {
            while (j > i && a[j] + a[i] > x)
                --j;
            cnt += j - i;
        }
        return cnt >= m;
    };
    while (l <= r)
    {
        int mid = (0ll + l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}