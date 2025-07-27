#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    int cnt = 0;

    const int mod = 1e9 + 7;
    long long ans = 1;
    for (int &x : a)
    {
        if (x == 1)
            ++cnt;
        else if (x % 2 == 0 && cnt > 0)
            --cnt, ++x;
        ans = (ans * x) % mod;

    }
    cout << ans << endl;
}