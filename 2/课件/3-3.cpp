#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int a[N], b[N], cnt[N];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    memcpy(b, a, sizeof a);
    sort(b, b + n);
    int len = unique(b, b + n) - b;
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(b, b + n, a[i]) - b + 1;
    int num = 0, ans = n + 1, ansl = -1, ansr = -1;
    for (int i = 0, j = 0; i < n; ++i)
    {
        while (j < n && num < m)
        {
            if (cnt[a[j]] == 0)
                ++num;
            ++cnt[a[j]];
        }
        if (num == m)
        {
            if (j - i + 1 < ans)
                ans = j - i + 1, ansl = i, ansr = j;
        }
        --cnt[a[i]];
        if (cnt[a[i]] == 0)
            --num;
    }
    cout << ansr << " " << ansl << endl;
}