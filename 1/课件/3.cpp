#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> x(n), v(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i];
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    double l = 0, r = 1e18, ans = 1e18;
    const double eps = 1e-7;
    auto check = [&](double use_time)
    {
        double right = 1e18, left = -1e18;
        for (int i = 0; i < n; ++i)
        {
            right = min(right, use_time * v[i] + x[i]);
            left = max(left, -use_time * v[i] + x[i]);
        }
        return right > left;
    };
    for (int i = 1; i <= 1000; ++i)
    {
        double mid = (l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    printf("%.5lf\n", ans);
}