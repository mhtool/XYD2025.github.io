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
    vector<int> len(n), mx(n);
    for (int i = 0, j = 0; i < n; ++i)
    {
        while (j < n && a[j] - a[i] <= k)
            ++j;
        len[i] = j - i;
    }
    for (int i = n - 1; i >= 0; --i)
    {
        mx[i] = len[i];
        if (i < n - 1)
            mx[i] = max(mx[i], mx[i + 1]);        
    } 
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int now = len[i];
        if (i + len[i] < n)
            now += mx[i + len[i]];
        ans = max(ans, now);
    }
    cout << ans << endl;
}