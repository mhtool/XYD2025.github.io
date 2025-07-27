#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> primes, is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i)
    {
        if (!is_prime[i])
            continue;
        primes.push_back(i);
        for (int j = i + i; j <= n; j += i)
            is_prime[j] = false;
    }
    for (int x : primes)
    {
        int now = n;
        long long res = 0;
        while (now)
        {
            res += now / x;
            now /= x;
        }
        cout << x << ' ' << res << '\n';
    }
}