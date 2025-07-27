#include <bits/stdc++.h>
using namespace std;
#define int long long
struct SegmentTree
{
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    struct Node
    {
        int val;
        int lazy_add;
        int lazy_mul;
        int len;
    };
    vector<Node> tr;
    int n, mod;
    SegmentTree(int _n, int _mod, vector<int> &a) : n(_n), mod(_mod)
    {
        tr.resize(n * 4);
        build(1, 1, n, a);
    }
    void push_up(int p)
    {
        tr[p].val = (tr[ls].val + tr[rs].val) % mod;
    }
    void update_add_mul(int p, int add, int mul)
    {
        tr[p].val = (1ll * tr[p].val * mul + 1ll * add * tr[p].len) % mod;
        tr[p].lazy_add = (1ll * tr[p].lazy_add * mul + add) % mod;
        tr[p].lazy_mul = (1ll * tr[p].lazy_mul * mul) % mod;
    }
    void push_down(int p)
    {
        update_add_mul(ls, tr[p].lazy_add, tr[p].lazy_mul);
        update_add_mul(rs, tr[p].lazy_add, tr[p].lazy_mul);

        tr[p].lazy_mul = 1;
        tr[p].lazy_add = 0;
    }
    void build(int p, int pl, int pr, vector<int> &a)
    {
        tr[p].len = pr - pl + 1;
        if (pl == pr)
        {
            tr[p].val = a[pl];
            return;
        }
        int mid = (pl + pr) >> 1;
        build(ls, pl, mid, a);
        build(rs, mid + 1, pr, a);
        push_up(p);
    }
    void update(int l, int r, int add, int mul, int p, int pl, int pr)
    {
        if (l == pl && pr == r)
        {
            update_add_mul(p, add, mul);
            return;
        }
        int mid = (pl + pr) >> 1;
        push_down(p);
        if (r <= mid)
            update(l, r, add, mul, ls, pl, mid);
        else if (l > mid)
            update(l, r, add, mul, rs, mid + 1, pr);
        else
            update(l, mid, add, mul, ls, pl, mid),
            update(mid + 1, r, add, mul, rs, mid + 1, pr);
        push_up(p);
    }
    int query(int l, int r, int p, int pl, int pr)
    {
        if (l == pl && pr == r)
            return tr[p].val;
        int mid = (pl + pr) >> 1;
        push_down(p);
        if (r <= mid)
            return query(l, r, ls, pl, mid);
        else if (l > mid)
            return query(l, r, rs, mid + 1, pr);
        else
            return (query(l, mid, ls, pl, mid) + query(mid + 1, r, rs, mid + 1, pr)) % mod;
    }
};

signed main()
{
    int n, q, mod;
    cin >> n >> q >> mod;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    SegmentTree tr(n, mod, a);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r, x;
            cin >> l >> r >> x;
            tr.update(l, r, 0, x % mod, 1, 1, n);
        }
        else if (op == 2)
        {
            int l, r, x;
            cin >> l >> r >> x;
            tr.update(l, r, x % mod, 1, 1, 1, n);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r, 1, 1, n) << endl;
        }
    }
}