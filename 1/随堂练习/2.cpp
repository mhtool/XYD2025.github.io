#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int l = 0, r = 4e5, ans = 4e5;
    auto check = [&](int limit)
    {
        int mx = a[0], mn = a[0];
        if (limit < a[0] + a[n - 1])
            return false;
        for (int i = 1; i < n; ++i)
        {
            int last_mx = mx, last_mn = mn;
            if (limit < a[i - 1] + a[i])
                return false;
            mx = min(a[i], a[0] - last_mn);
            int last_other = a[i - 1] - last_mx;
            int now_other = limit - a[0] - last_other;
            int now_in = a[i] - now_other;
            mn = max(0, now_in);
        }
        return mn == 0;
    };
    check(7);
}