#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    // vector<int> cnt(m + 1);
    map<int, int> cnt;
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