#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, k, p;
    cin >> n >> k >> p;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    vector<int> cnt(k);
    long long ans = 0;
    for (int i = 0, j = 0; i < n; ++i)
    {
        if (b[i] <= p)
        {
            while (j <= i)
            {
                ++cnt[a[j]];
                ++j;
            }
            --ans;
        }
        ans += cnt[a[i]];
    }
    cout << ans << '\n';
}