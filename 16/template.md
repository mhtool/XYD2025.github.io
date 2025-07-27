## 树状数组

![[Pasted image 20250727081939.png]]

```cpp
// 最不需要知道他是怎么做的一个数据结构
struct FenwickTree
{
    vector<int> c;
    int n;
    FenwickTree(int _n) : n(_n)
    {
        c.resize(n + 1);
    }
    // a[x] += y;
    void add(int x, int y)
    {
		while (x <= n)
            c[x] += y, x += lowbit(x);
    }
    // a[1] + a[2] + ... + a[x];
    int query(int x)
    {
        int res = 0;
		while (x)
            res += c[x], x -= lowbit(x);
        return res;
    }
};

struct FenwickTree
{
    vector<int> c;
    int n;
    FenwickTree(int _n) : n(_n)
    {
        c.resize(n + 1);
    }
    // a[x] += y;
    void add(int x, int y)
    {
		while (x)
            c[x] += y, x -= lowbit(x);
    }
    // a[x] + a[x + 1] + ... + a[n];
    int query(int x)
    {
        int res = 0;
		while (x <= n)
            res += c[x], x += lowbit(x);
        return res;
    }
};
int main()
{
	int n;
	vector<int> a(n + 1);
	
	// 离散化
	// 按照其中一维排序
	FenwickTree tr(n);
	for (int i = 1; i <= n; ++i)
	{
		ans += tr.query(a[i].y);
		
		tr.add(a[i].y);
		
	}
	

}
```



## 线段树


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct SegmentTree
{
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    // 单点修改
    // 区间查询
    struct Node
    {
        int len;
        ll val;
        ll lazy;
        Node(int x) : val(x), lazy(0) {}
    };
    
    // 合并两个节点
    Node merge(Node a, Node b)
    {
        Node res;
        res.val = max(a.val, b.val);
        return res;
    }

    vector<Node> tr;
    int n;

    SegmentTree(int _n, vector<int> &a) : n(_n)
    {
        tr.resize(n * 4);
        build(1, 1, n, a);
    }
	void update_node(int p, int x)
	{
		tr[p].val += x;
		tr[p].lazy += x;
	}
    // 向上更新
    void push_up(int p)
    {
        tr[p] = merge(tr[ls], tr[rs]);
    }
    // 向下更新
    void push_down(int p)
    {
	    update_node(ls, tr[p].lazy);
	    update_node(rs, tr[p].lazy);
	    tr[p].lazy = 0;
    }
    // 建树
    void build(int p, int pl, int pr, vector<int> &a)
    {
	    tr[p].len = pr - pl + 1;
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
    // 单点修改
    void update(int x, int y, int p, int pl, int pr)
    {
        if (pl == pr)
        {
			update_node(p, y);
            return;
        }
        push_down(p);
        int mid = (pl + pr) >> 1;
        if (x <= mid)
            update(x, y, ls, pl, mid);
        else if (x > mid)
            update(x, y, rs, mid + 1, pr);
        push_up(p);
    }
    // 区间修改
    void update(int l, int r, int x, int p, int pl, int pr)
    {
		if (l == pl && pr == r)
		{
			update_node(p, x);
			return;
		}
        push_down(p);
        int mid = (pl + pr) >> 1;
        if (r <= mid)
            update(l, r, x, ls, pl, mid);
        else if (l > mid)
            update(l, r, x, rs, mid + 1, pr);
        else
			update(l, mid, x, ls, pl, mid), update(mid + 1, r, x, rs, mid + 1, pr);
		push_up(p);
    }
    // 区间查询
    Node query(int l, int r, int p, int pl, int pr)
    {
        if (l == pl && pr == r)
            return tr[p];
        push_down(p);
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
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i= 1; i <= n; ++i)
		cin >> a[i];
	SegmentTree tr(n, a);
	int q;
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int x, y;
			cin >> x >> y;
			tr.update(x, y, 1, 1, n);
		}
		else 
		{
			int l, r;
			cin >> l >> r;
			cout << tr.query(l, r, 1, 1, n).res << endl;
		}
	}
}

```