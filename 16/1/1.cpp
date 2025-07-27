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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    FenwickTree tr(n);
    for (int i = 1; i <= n; ++i)
        tr.add(i, a[i] - a[i - 1]);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r, x;
            cin >> l >> r >> x;
            tr.add(l, x);
            tr.add(r + 1, -x);
        }
        else
        {
            int p;
            cin >> p;
            cout << tr.query(p) << endl;
        }
    }
}