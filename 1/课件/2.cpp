#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int main()
{
    int L, n, m;
    cin >> L >> n >> m;
    vector<int> d(n + 2);
    for (int i = 1; i <= n; ++i)
        cin >> d[i];
    d[n + 1] = L;
    int l = 1, r = L, ans = 0;
    auto check = [&](int t) 
    {
        int last = 0;
        int cnt = 0;
        for (int i = 1; i <= n + 1; ++i)
        {
            if (d[i] - last < t)
                ++cnt;
            else
                last = d[i];
        }
        return cnt <= m;
    };
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            l = mid + 1;
            ans = mid;
        }
        else
            r = mid - 1;
    }
    cout << ans << endl;
}