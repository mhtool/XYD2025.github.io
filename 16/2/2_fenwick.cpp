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
            c[i] ^= y;
    }
    int query(int x)
    {
        int res = 0;
        for (int i = x; i; i -= i & -i)
            res ^= c[i];
        return res;
    }
};


int main()
{
    int n, q;
    cin >> n >> q;
    FenwickTree tr(n);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r;
            cin >> l >> r;
            tr.add(l, 1);
            tr.add(r + 1, 1);
        }
        else
        {
            int x;
            cin >> x;
            cout << tr.query(x) << endl;
        }
    }
}