#include <bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> lens(n);
    for (int i = 0; i < n; ++i)
        cin >> lens[i];
    int limit = *max_element(lens.begin(), lens.end());
    int l = 1, r = limit, ans = 1;
    auto check = [&](int mid)
    {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            cnt += lens[i] / mid;
        return cnt >= m;
    };
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << ans << '\n';
    return 0;
}