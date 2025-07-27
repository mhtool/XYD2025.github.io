#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<int> series;
    vector<int> pos(n);

    for (int i = 0; i < n; ++i)
    {
        auto it = lower_bound(series.begin(), series.end(), a[i]);
        pos[i] = it - series.begin();
        if (it == series.end())
            series.push_back(a[i]);
        else
            *it = a[i];
    }

    int len = series.size();

    vector<int> lis(len);
    int cur_len = len;
    for (int i = n - 1; i >= 0; --i)
    {
        if (pos[i] == cur_len - 1)
        {
            lis[--cur_len] = a[i];
            if (cur_len == 0)
                break;
        }
    }

    for (int x : lis)
        cout << x << " ";
    cout << "\n";

    return 0;
}
