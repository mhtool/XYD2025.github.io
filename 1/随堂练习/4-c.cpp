#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct Node
{
    double x, y;
};
bool cmpX(Node n1, Node n2)
{
    return n1.x < n2.x;
}
bool cmpY(Node n1, Node n2)
{
    return n1.y < n2.y;
}
double dis(Node n1, Node n2)
{
    return (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
}
Node points[N];
Node tmps[N];
Node mids[N];
int mid_len;
long long solve(int l, int r)
{
    if (l == r)
        return 1e18;
    int mid = (l + r) / 2;
    long long d = min(solve(l, mid), solve(mid + 1, r));
    double sqrtD = sqrt(d);
    int midX = points[mid].x;
    for (int i = l; i <= r; ++i)
        tmps[i] = points[i];
    for (int i = l, j = mid + 1, k = l; i <= mid || j <= r;)
    {
        if (tmps[i].y < tmps[j].y)
            points[k++] = tmps[i++];
        else
            points[k++] = tmps[j++];
    }
    mid_len = 0;
    midsleft
    midsright
    for (int i = l; i <= r; ++i)
        if ((mids[i].x - midX) < 0 && > -sqrtD)
            mids[++mid_len] = points[i];
    // sort(mids + 1, mids + mid_len + 1, cmpY);

    for (int i = 1; i <= mid_len; ++i)
        for (int j = i + 1; j <= mid_len; ++j)
        {
            if (mids[j].y - mids[i].y > sqrtD)
                break;
            d = min(dis(mids[i], mids[j]), d);
        }
    return d;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> points[i].x >> points[i].y;
    sort(points + 1, points + n + 1, cmpX);
    cout << sqrt(solve(1, n)) << endl;
}
