#include <bits/stdc++.h>
using namespace std;

const int DEFAULT_BASE = 233;
const int DEFAULT_MOD = 1e9 + 7;

struct StringHash
{
    int base;
    int mod;
    int n;
    vector<int> pw;
    vector<int> hash;
    StringHash(string s, int base = DEFAULT_BASE, int mod = DEFAULT_MOD)
    {
        this->base = base;
        this->mod = mod;
        n = s.size();
        s = " " + s;
        hash.resize(n + 1);
        pw.resize(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            hash[i] = (1ll * hash[i - 1] * base + s[i]) % mod;
            pw[i] = 1ll * pw[i - 1] * base % mod;
        }
    }
    int get_hash(int l, int r)
    {
        return (hash[r] - 1ll * hash[l - 1] * pw[r - l + 1] % mod + mod) % mod;
    }
};

struct StringHashUll
{
    using ull = unsigned long long;
    int base;
    int n;
    vector<ull> pw;
    vector<ull> hash;
    StringHashUll(string s, int base = DEFAULT_BASE)
    {
        this->base = base;
        n = s.size();
        s = " " + s;
        hash.resize(n + 1);
        pw.resize(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            hash[i] = hash[i - 1] * base + s[i];
            pw[i] = pw[i - 1] * base;
        }
    }
    ull get_hash(int l, int r)
    {
        return hash[r] - hash[l - 1] * pw[r - l + 1];
    }
};