#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0, j = 0; i < n; ++i)
    {
        while (j < n && a[j] - a[i] <= k)
            ++j;
        ans = max(ans, j - i);
    }
    cout << ans << endl;
}