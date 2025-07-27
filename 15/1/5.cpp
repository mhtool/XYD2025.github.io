#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
        cin >> a[i];
    auto b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    using ll = long long;
    vector<ll> last(b.size(), -1e18);
    ll now = 0;
    for (int x : a)
    {
        ++now;
        ll space = now - last[x];
        if (space <= m)
            now = last[x] + m + 1;

        last[x] = now;
    }
    cout << now << endl;
    return 0;
}