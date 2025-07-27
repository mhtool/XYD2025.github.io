#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    using Point = pair<double, double>;
    vector<Point> points;
    for (int i = 0; i < n; ++i)
    {
        double x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    sort(points.begin(), points.end());
    auto dis = [](Point a, Point b)
    {
        auto pow = [](double x, double y)
        { return x * x + y * y; };
        return pow(a.first - b.first, a.second - b.second);
    };
    auto closest = [&](auto &&self, auto l, auto r) -> double
    {
        if (r - l == 1)
            return LONG_LONG_MAX;
        auto mid = l + (r - l) / 2;
        double midX = mid->first;
        double d = min(self(self, l, mid), self(self, mid, r));
        double sqrtD = sqrt(d);
        inplace_merge(l, mid, r, [](Point a, Point b)
                      { return a.second < b.second; });
        vector<decltype(l)> mids;
        for (auto it = l; it != r; ++it)
            if (abs(it->first - midX) < sqrtD)
                mids.push_back(it);
        for (auto it = mids.begin(); it != mids.end(); ++it)
            for (auto jt = next(it); jt != mids.end() && (*jt)->second - (*it)->second < sqrtD; ++jt)
                d = min(d, dis(**it, **jt));
        return d;
    };
    printf("%.2f\n", 2 * sqrt(closest(closest, points.begin(), points.end())) / 2);
}
