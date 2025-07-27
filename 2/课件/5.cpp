#include <bits/stdc++.h>
using namespace std;
int main()
{
    int q;
    cin >> q;
    vector<int> a;
    int idx = 0;
    long long sum = 0;
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x;
            cin >> x;
            if (!a.empty())
                sum -= a.back();
            a.push_back(x);
            sum += a.back();
            while (idx < a.size() - 1 && 1ll * a[idx] * (idx + 1) < sum)
                sum += a[idx++];
        }
        else
        {
            printf("%.10lf\n", a.back() - sum * 1. / (idx + 1));
        }
    }
}