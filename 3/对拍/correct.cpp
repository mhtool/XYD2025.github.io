#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("data.in", "r", stdin);
    freopen("correct.out", "w", stdout);
    int n, m, x, y, z;
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &z);
    vector<int> a(x), b(y), c(z);
    for (auto &i : a)
        cin >> i;
    for (auto &i : b)
        cin >> i;
    for (auto &i : c)
        cin >> i;
    int ans = 0;
    for (int i = 0; i < (1 << x); ++i)
        for (int j = 0; j < (1 << y); ++j)
            for (int k = 0; k < (1 << z); ++k)
            {
                int sum = 0;
                int cnt1 = 0, cnt2 = 0, cnt3 = 0;
                for (int i1 = 0; i1 < x; ++i1)
                    if (i >> i1 & 1)
                        sum += a[i1], ++cnt1;
                for (int j1 = 0; j1 < y; ++j1)
                    if (j >> j1 & 1)
                        sum += b[j1], ++cnt2;
                for (int k1 = 0; k1 < z; ++k1)
                    if (k >> k1 & 1)
                        sum += c[k1], ++cnt3;
                if (cnt1 <= n && cnt2 <= m && cnt1 + cnt2 + cnt3 == n + m)
                {
                    ans = max(ans, sum);
                }
            }
    cout << ans << endl;
}