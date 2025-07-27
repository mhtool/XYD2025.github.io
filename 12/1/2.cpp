#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    using Point = pair<int, int>;
    vector<Point> points(n);
    vector<int> x_coords(n), y_coords(n);
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
        x_coords[i] = x;
        y_coords[i] = y;
    }
    sort(x_coords.begin(), x_coords.end());
    sort(y_coords.begin(), y_coords.end());
    auto get_pos = [&](int x, const vector<int> &coords)
    {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin() + 1;
    };

    vector<vector<int>> grid(n + 1, vector<int>(n + 1, 0));

    for (auto &[x, y] : points)
    {
        x = get_pos(x, x_coords);
        y = get_pos(y, y_coords);
        ++grid[x][y];
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];

    auto get_sum = [&](int x1, int y1, int x2, int y2)
    {
        if (x1 > x2 || y1 > y2)
            return 0;
        return grid[x2][y2] -
               grid[x1 - 1][y2] -
               grid[x2][y1 - 1] +
               grid[x1 - 1][y1 - 1];
    };

    sort(points.begin(), points.end());

    long long ans = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            auto [x1, y1] = points[i];
            auto [x2, y2] = points[j];
            if (y1 > y2)
                swap(y1, y2);
            int cnt1 = get_sum(x1, 1, x2, y1);
            int cnt2 = get_sum(x1, y2, x2, n);
            // cout << cnt1 << ' ' << cnt2 << '\n';
            assert(i + 1 == x1);
            assert(j + 1 == x2);
            ans += 1ll * cnt1 * cnt2;
        }
    }
    cout << ans + 1 << endl;
}