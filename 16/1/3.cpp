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

using Star = array<int, 3>;

/*
equals

struct Star
{
    int x, y, id;
    bool operator<(const Star &o) const
    {
        return x < o.x || (x == o.x && y < o.y);
    }
};
*/

int main()
{
    int n;
    cin >> n;
    vector<Star> a(n);
    int max_y = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i][0] >> a[i][1];
        ++a[i][0];
        ++a[i][1];
        a[i][2] = i;
        max_y = max(max_y, a[i][1]);
    }
    FenwickTree tr(max_y + 1);
    sort(a.begin(), a.end());
    vector<int> ans(n);
    for (auto [x, y, id] : a)
    {
        ans[id] = tr.query(y);
        tr.add(y, 1);
    }

    vector<int> ans_cnt(n);
    for (auto x : ans)
        ++ans_cnt[x];
    for (auto x : ans_cnt)
        cout << x << endl;
}