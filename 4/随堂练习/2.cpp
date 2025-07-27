#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

void solve()
{
    int n;
    double p0;
    cin >> p0 >> n;
    vector<int> val(n); 
    vector<double> p(n);
    for (int i = 0; i < n; ++i)
        cin >> val[i] >> p[i];
    int sum = accumulate(val.begin(), val.end(), 0);
    vector<double> dp(sum + 1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = sum; j >= val[i]; --j)
            dp[j] = max(dp[j], dp[j - val[i]] * (1 - p[i]));
    int ans = 0;
    for (int i = 0; i <= sum; ++i)
        if (1- dp[i] + eps < p0)
            ans = i;
    cout << ans << endl;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();

}