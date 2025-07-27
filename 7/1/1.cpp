#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    class ST_Table
    {
    private:
        int n;
        vector<vector<int>> st;
        vector<int> lg;
        function<int(int, int)> func;

    public:
        ST_Table(const vector<int> &arr, function<int(int, int)> f) : func(f)
        {
            n = arr.size();
            lg.resize(n + 1);
            for (int i = 2; i <= n; ++i)
                lg[i] = lg[i >> 1] + 1;
            int k = lg[n];
            st.assign(n, vector<int>(k + 1));
            for (int i = 0; i < n; ++i)
                st[i][0] = arr[i];
            for (int j = 1; j <= k; ++j)
                for (int i = 0; i + (1 << j) <= n; ++i)
                    st[i][j] = func(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
        int query(int l, int r)
        {
            int j = lg[r - l + 1];
            return func(st[l][j], st[r - (1 << j) + 1][j]);
        }
    };
    ST_Table mx(a, [](int x, int y)
                { return max(x, y); });
    ST_Table mn(a, [](int x, int y)
                { return min(x, y); });
    auto query = [&](int l, int r)
    {
        return mx.query(l, r) - mn.query(l, r);
    };
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;
        cout << query(l, r) << '\n';
    }
}