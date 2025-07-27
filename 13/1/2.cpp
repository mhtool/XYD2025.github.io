#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 5e5 + 5;

vector<int> primes;
vector<int> prime(LIMIT + 1, true);
void init_prime(int n = LIMIT)
{
    prime[0] = prime[1] = false;
    for (int i = 2; i <= n; ++i)
    {
        if (!prime[i])
            continue;
        primes.push_back(i);
        for (auto j = 1ll * i * i; j <= n; j += i)
            prime[j] = false;
    }
}


int main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    init_prime(n);
    const int mod = 1e9 + 7;
    vector<int> dp(n + 1);
    dp[1] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j : primes)
        {
            if (i * j > n)
                break;
            dp[i * j] = (dp[i * j] + dp[i]) % mod;
        }
    }
    for (int x; q--;)
    {
        cin >> x;
        cout << dp[x] << '\n';
    }
}