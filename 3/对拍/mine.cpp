#include <bits/stdc++.h>
using namespace std;
struct a
{
    int p, i;
} t[300009];
bool check(a x, a y)
{
    return x.i > y.i;
}
int main()
{
    freopen("data.in", "r", stdin);
    freopen("mine.out", "w", stdout);
    int n, m, x, y, z;
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &z);
    for (int i = 0; i < x; i++)
    {
        scanf("%d", &t[i].i);
        t[i].p = 0;
    }
    for (int i = x; i < x + y; i++)
    {
        scanf("%d", &t[i].i);
        t[i].p = 1;
    }
    for (int i = y + x; i < x + y + z; i++)
    {
        scanf("%d", &t[i].i);
        t[i].p = 2;
    }
    sort(t, t + x + y + z, check);
    int i = 0, x1 = 0, y1 = 0, z1 = 0;
    long long num = 0;
    while (x1 + y1 + z1 != n + m)
    {
        if (t[i].p == 0 && x1 > x)
        {
            x1++;
            num += t[i].i;
        }
        else if (t[i].p == 1 && y1 > y)
        {
            y1++;
            num += t[i].i;
        }
        else
        {
            z1++;
            num += t[i].i;
        }
        i++;
    }
    printf("%lld", num);
    return 0;
}