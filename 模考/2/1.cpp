#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> cnt1(5005), cnt2(5005);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        cin >> x >> y;
        ans += cnt1[x + y];
        ans += cnt2[x - y + 1002];
        ++cnt1[x + y];
        ++cnt2[x - y + 1002];
    }
    cout << ans << endl;
}