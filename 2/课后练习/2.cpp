#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pos(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i], pos[a[i]] = i;

    int l = n - 1, r = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i)
    {
        l = min(l, pos[i]);
        r = max(r, pos[i]);
        auto get_ans = [&](int len) 
        {
            if (len > n)
                return 0;
            int minL = max(0, r - len + 1);
            int maxL = min(l, n - len);
            return max(0, maxL - minL + 1);
        };
        ans += get_ans(i * 2 + 1);
        ans += get_ans(i * 2 + 2);
    }
    cout << ans << endl;
}