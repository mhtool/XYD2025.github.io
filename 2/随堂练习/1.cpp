#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    int mid = n / 2;
    auto left = vector<int>(a.begin(), a.begin() + mid);
    auto right = vector<int>(a.begin() + mid, a.end());

    auto get_ans = [&](const auto &v)
    {
        map<long long, int> cnt;
        int n = v.size();
        int S = 1 << n;
        for (int i = 0; i < S; ++i)
        {
            long long sum = 0;
            for (int j = 0; j < n; ++j)
                if (i & (1 << j))
                    sum += v[j];
            ++cnt[sum];
        }
        return cnt;
    };
    auto left_cnt = get_ans(left);
    auto right_cnt = get_ans(right);
    int ans = 0;
    for (auto [val, cnt] : left_cnt)
    {
        ans += cnt * right_cnt[m - val];
    }
    cout << ans << endl;
}