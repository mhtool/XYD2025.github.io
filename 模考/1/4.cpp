#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
    vector<long long> dp(k + 1);
    dp[0] = 1;
    using func = pair<int, int>;
    // a2(a1 x + b1) + b2 > (a1 (a2 x + b2) + b1)
    // a2 * a1 x + a2 * b1 + b1 > a1 * a2 x + a1 * b2 + b1
    // a2 * b1 + b2 > a1 * b2 + b1
    auto cmp = [](const func &a, const func &b)
    {
        auto [a1, b1] = a;
        auto [a2, b2] = b;
        return a2 * b1 + b2 > a1 * b2 + b1;
    };

    vector<func> funcs;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        funcs.emplace_back(a, b);
    }
    sort(funcs.begin(), funcs.end(), cmp);
    for (auto &[a, b] : funcs)
    {
        for (int j = k; j >= 1; --j)
            dp[j] = max(dp[j - 1] * a + b, dp[j]);
    }
    cout << dp[k] << endl;
}