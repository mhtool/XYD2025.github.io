#include <bits/stdc++.h>
using namespace std;

struct SegmentTree
{
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    vector<int> mx, lazy;
    int n;
    SegmentTree(int _n) : n(_n)
    {
        mx.resize(n * 4);
        lazy.resize(n * 4);
    }
    void push_up(int p)
    {
        mx[p] = max(mx[ls], mx[rs]);
    }
    void push_down(int p)
    {
        mx[ls] += lazy[p];
        mx[rs] += lazy[p];
        lazy[ls] += lazy[p];
        lazy[rs] += lazy[p];
        lazy[p] = 0;
    }
    void build(int p, int pl, int pr)
    {
        if (pl == pr)
        {
            mx[p] = 0;
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
            mx[p] += x;
            lazy[p] += x;
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
            return mx[p];
        int mid = (pl + pr) >> 1;
        push_down(p);
        if (r <= mid)
            return query(l, r, ls, pl, mid);
        else if (l > mid)
            return query(l, r, rs, mid + 1, pr);
        else
            return max(query(l, mid, ls, pl, mid), query(mid + 1, r, rs, mid + 1, pr));
    }
};

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    SegmentTree tr(n);
    tr.build(1, 1, n);
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        --r;
        if (tr.query(l, r, 1, 1, n) + x > m)
            cout << "N" << endl;
        else
            cout << "T" << endl,
            tr.update(l, r, x, 1, 1, n);
    }
}