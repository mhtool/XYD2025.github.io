#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int p = 1 << n;
    auto mat = vector(p, vector<int>(p));
    auto run = [&](auto &&self, int l, int u, int t) -> void
    {
        if (t == 1)
            mat[l][u + 1] = mat[l + 1][u] = mat[l + 1][u + 1] = 1;
        else
        {
            int p = 1 << (t - 1);
            self(self, l + p, u, t - 1);
            self(self, l, u + p, t - 1);
            self(self, l + p, u + p, t - 1);
        }
    };
    run(run, 0, 0, n);
    for (auto v : mat)
    {
        for (auto x : v)
            printf("%d ", x);
        puts("");
    }
}