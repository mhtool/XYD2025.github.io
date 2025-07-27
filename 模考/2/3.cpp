#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
using ll = long long;

int qpow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
        b >>= 1;
    }
    return res; 
}   

int get_inv(int x)
{
    return qpow(x, MOD - 2);
}

int div_mod(int a, int b)
{
    return 1ll * a * get_inv(b) % MOD;
}

int main()
{
    int n;
    cin >> n;
    int m = n * 2;
    vector<int> a(m + 1);
    for (int i = 1; i <= m; ++i)
        cin >> a[i];

    int sum = accumulate(a.begin() + 1, a.begin() + n + 1, 0LL) % MOD;
    int unlock = n;
    int ans = 0;
    int pre = 0;

    for (int i = 1; i <= m; ++i)
    {
        int cur = div_mod(sum, unlock - i + 1);
        pre = (pre + cur) % MOD;
        ans = (ans + pre) % MOD;
        sum = (sum - cur + MOD) % MOD;
        if (unlock < m)
            sum = (sum + a[++unlock]) % MOD;
    }

    cout << ans << endl;
}

