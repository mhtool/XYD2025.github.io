#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    map<pair<int, int>, int> mp;
    int idx, h;
    cin >> idx >> h;
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        if (l > r)
            swap(l, r);
        if (!mp[{l, r}])
        {
            mp[{l, r}] = 1;
            a[l + 1] -= 1;
            a[r] += 1;
        }
    }
    for (int i = 1; i <= n; ++i)
        a[i] += a[i - 1];
    auto get_height = [&](int x)
    {
        return a[x] - a[idx] + h;
    };
    for (int i = 1; i <= n; ++i)
        cout << get_height(i) << endl;
}