#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, W;
    cin >> n >> W;
    struct item
    {
        int v, w;
    };
    vector<item> items(n), items_divided;
    vector<int> m(n), f(W + 1);
    for (int i = 0; i < n; ++i)
        cin >> items[i].v >> items[i].w >> m[i];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j <= m[i]; m[i] -= j, j <<= 1) // 13 1101 // 001 010 100 // 0 ~ 7  6 // 0 ~ 13
            items_divided.push_back({j * items[i].v, j * items[i].w});
        if (m[i] > 0)
            items_divided.push_back({m[i] * items[i].v, m[i] * items[i].w})
    }
    for (auto [v, w] : items_divided)
        for (int j = W; j >= w; --j)
            f[j] = max(f[j], f[j - w] + v);
    cout << f[W] << endl;
}