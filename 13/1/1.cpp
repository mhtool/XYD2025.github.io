#include <bits/stdc++.h>
using namespace std;

const int LIMIT = sqrt(INT_MAX) * 2;


vector<int> primes;
vector<int> prime(LIMIT + 1, true);
void init_prime()
{
    prime[0] = prime[1] = false;
    for (int i = 2; i <= sqrt(n) + 1; ++i)
    {
        if (!prime[i])
            continue;
        primes.push_back(i);
        for (int j = i + i; j <= n; j += i)
            prime[j] = false;
    }
    for (int i = sqrt(n) + 2; i <= n; ++i)
        if (prime[i])
            primes.push_back(i);
}


vector<int> euler_phi(int n) {
    vector<int> phi(n + 1);
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                break;
            }
        }
    }
    return phi;
}
int is_prime(int x)
{
    if (x <= LIMIT)
        return prime[x];
    for (int p : primes)
    {
        if (1ll * p * p > x)
            break;
        if (x % p == 0)
            return false;
    }
    return true;
}

int main()
{
    init_prime();
    int n, m;
    cin >> n >> m;
    for (long long i = n; i <= m; ++i)
        if (is_prime(i))
            cout << i << " ";
}