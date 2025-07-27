#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    vector<int> val, lazy;
    int n;
    SegmentTree(int _n) : n(_n)
    {
        val.resize(n * 4);
        lazy.resize(n * 4);
    }
    void push_up(int p)
    {
        val[p] = val[ls] ^ val[rs];
    }
    void push_down(int p)
    {
        val[ls] ^= lazy[p];
        val[rs] ^= lazy[p];
        lazy[ls] ^= lazy[p];
        lazy[rs] ^= lazy[p];
        lazy[p] = 0;
    }
    void build(int p, int pl, int pr)
    {
        if (pl == pr)
        {
            val[p] = 0;
            return;
        }
        int mid = (pl + pr) >> 1;
        build(ls, pl, mid);
        build(rs, mid + 1, pr);
        push_up(p);
    }
    void update(int l, int r, int x, int p, int pl, int pr)
    {
        if (l == pl && pr == r)
        {
            val[p] ^= x;
            lazy[p] ^= x;
            return;
        }
        int mid = (pl + pr) >> 1;
        push_down(p);
        if (r <= mid)
            update(l, r, x, ls, pl, mid);
        else if (l > mid)
            update(l, r, x, rs, mid + 1, pr);
        else
            update(l, mid, x, ls, pl, mid),
            update(mid + 1, r, x, rs, mid + 1, pr);
        push_up(p);
    }
    int query(int l, int r, int p, int pl, int pr)
    {
        if (l == pl && pr == r)
            return val[p];
        int mid = (pl + pr) >> 1;
        push_down(p);
        if (r <= mid)
            return query(l, r, ls, pl, mid);
        else if (l > mid)
            return query(l, r, rs, mid + 1, pr);
        else
            return query(l, mid, ls, pl, mid) ^ query(mid + 1, r, rs, mid + 1, pr);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    SegmentTree tr(n);
    tr.build(1, 1, n);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r;
            cin >> l >> r;
            tr.update(l, r, 1, 1, 1, n);
        }
        else
        {
            int x;
            cin >> x;
            cout << tr.query(x, x, 1, 1, n) << endl;
        }
    }
}