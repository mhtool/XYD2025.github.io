#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct SegmentTree
{
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    // 维护最大连续和
    // 单点修改
    // 区间查询
    struct Node
    {
        ll ans, sum, lmx, rmx;
        Node() : ans(0), sum(0), lmx(0), rmx(0) {}
        Node(int x)
        {
            sum = x;
            ans = lmx = rmx = max(0, x);
        }
    };
    
    Node merge(Node a, Node b)
    {
        Node res;
        res.ans = max(a.ans, b.ans);
        res.ans = max(res.ans, a.rmx + b.lmx);
        res.lmx = max(a.lmx, a.sum + b.lmx);
        res.rmx = max(b.rmx, b.sum + a.rmx);
        res.sum = a.sum + b.sum;
        return res;
    }



    vector<Node> tr;
    int n;

    SegmentTree(int _n, vector<int> &a) : n(_n)
    {
        tr.resize(n * 4);
        build(1, 1, n, a);
    }

    void push_up(int p)
    {
        tr[p] = merge(tr[ls], tr[rs]);
    }
    void build(int p, int pl, int pr, vector<int> &a)
    {
        if (pl == pr)
        {
            tr[p] = Node(a[pl]);
            return;
        }
        int mid = (pl + pr) >> 1;
        build(ls, pl, mid, a);
        build(rs, mid + 1, pr, a);
        push_up(p);
    }
    void update(int x, int y, int p, int pl, int pr)
    {
        if (pl == pr)
        {
            tr[p] = Node(y);
            return;
        }
        int mid = (pl + pr) >> 1;
        if (x <= mid)
            update(x, y, ls, pl, mid);
        else if (x > mid)
            update(x, y, rs, mid + 1, pr);
        push_up(p);
    }
    Node query(int l, int r, int p, int pl, int pr)
    {
        if (l == pl && pr == r)
            return tr[p];
        int mid = (pl + pr) >> 1;
        if (r <= mid)
            return query(l, r, ls, pl, mid);
        else if (l > mid)
            return query(l, r, rs, mid + 1, pr);
        else
            return merge(query(l, mid, ls, pl, mid), query(mid + 1, r, rs, mid + 1, pr));
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    SegmentTree tr(n, a);
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        tr.update(x, y, 1, 1, n);
        cout << tr.query(1, n, 1, 1, n).ans << endl;
    }
    return 0;
}