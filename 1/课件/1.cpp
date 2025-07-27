#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int n, q;
int a[N], sum[N];

bool check1(int idx, int t)
{
    return sum[idx - 1] <= t;
}
bool check2(int idx, int t)
{
    return sum[idx] > t;
}
int solve1(int t)
{
    int l = 1, r = n;
    int ans = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check1(mid, t))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    return ans;
}
int solve2(int t)
{
    int l = 1, r = n;
    int ans = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check2(mid, t))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    return ans;
}
int solve3(int t)
{
    return upper_bound(sum + 1, sum + n + 1, t) - sum;
}
int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i];
    while (q--)
    {
        int t;
        cin >> t;
        cout << solve2(t) << endl;
    }
}