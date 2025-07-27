#include <bits/stdc++.h>
using namespace std;

void init(auto &a)
{
    auto b = a;
    sort(b.begin(), b.end());
    auto it = unique(b.begin(), b.end());
    b.erase(it, b.end());
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1; // 1 ... m;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    init(a);
    vector<int> cnt(m + 1);
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