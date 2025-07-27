#include <bits/stdc++.h>
using namespace std;
struct Vec
{
    int x, y;
    // 向量点积
    // a * b
    long long operator*(const Vec &b) const
    {
        return 1ll * x * b.x + 1ll * y * b.y;
    }
    // 向量叉积
    // a ^ b
    long long operator^(const Vec &b) const
    {
        return 1ll * x * b.y - 1ll * y * b.x;
    }
};
struct Point
{
    int x, y;
    void input()
    {
        cin >> x >> y;
    }
    // vector 向量
    Vec operator-(const Point &b) const
    {
        return {x - b.x, y - b.y};
    }

};

long long get_dis_2(Point a, Point b)
{
    return 1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y);
}

double get_dis(Point a, Point b)
{
    return sqrt(get_dis_2(a, b));
}

long long in_middle(Point a, Point b, Point c)
{
    Vec ba = b - a; // a -> b
    Vec bc = b - c; // c -> b
    return (ba ^ bc) == 0 && (ba * bc) <= 0;
}

int main()
{
    int n, m;
    vector<Point> p(1);
    p[0].input();
    cin >> n >> m;
    p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        p[i].input();
    vector<Point> q(m);
    for (int i = 0; i < m; i++)
        q[i].input();
    vector<vector<double>> dis(n + 1, vector<double>(n + 1, 1e18));
    for (int i = 1;  i <= n; ++i)
        dis[i][0] = get_dis(p[i], p[0]) * 2;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int flag = 1;
            for (int k = 0; k < m && flag; ++k)
                if (in_middle(p[i], q[k], p[j]))
                    flag = 0;
            if (flag)
                dis[i][j] = min(dis[i][j], get_dis(p[i], p[j]));
        }
    
    for (int k = 0; k <= n; ++k)
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    printf("%.0lf\n", dis[1][0]);
}