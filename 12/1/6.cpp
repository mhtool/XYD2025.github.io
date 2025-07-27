#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, k;
    cin >> k >> n;

    vector<int> cnt(k + 1);

    int now = 0;
    long long ans = 0;
    ++cnt[0]; // sum[r] - sum[l - 1]  l - 1  取到 0 
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        now += x;
        now %= k;
        ans += cnt[now];
        ++cnt[now];
    }
    cout << ans << endl;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}