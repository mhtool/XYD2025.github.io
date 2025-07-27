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
    FenwickTree left(n), right(n);
    int cnt = 0;
    while (q--)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
        {
            left.add(l, 1);
            right.add(r, 1);
            ++cnt;
        }
        else
        {
            int left_ans = right.query(l - 1);
            int right_ans = left.query(n) - left.query(r);
            int ans = cnt - (left_ans + right_ans);
            cout << ans << endl;
        }
    }
}