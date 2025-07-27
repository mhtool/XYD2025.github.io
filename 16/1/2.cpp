#include <bits/stdc++.h>
using namespace std;

struct FenwickTree
{
    vector<int> c;
    int n;
    FenwickTree(int _n) : n(_n)
    {
        c.resize(n + 1);
    }
    void add(int x, int y)
    {
        for (int i = x; i <= n; i += i & -i)
            c[i] += y;
    }
    int query(int x)
    {
        int res = 0;
        for (int i = x; i; i -= i & -i)
            res += c[i];
        return res;
    }
};


int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    FenwickTree tr(*max_element(a.begin(), a.end()) + 1);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += (i - 1) - tr.query(a[i]);
        tr.add(a[i], 1);
    }
    cout << ans << endl;
}