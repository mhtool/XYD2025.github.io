#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, l1, l2, l3;
    cin >> n >> m >> l1 >> l2 >> l3;
    vector<int> a(l1), b(l2), c(l3);
    for (int &x : a)
        cin >> x;
    for (int &x : b)
        cin >> x;
    for (int &x : c)
        cin >> x;
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());
    sort(c.begin(), c.end(), greater<int>());   

    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 0; i < l1 && i < n; ++i)
        q.push(a[i]);
    for (int i = 0; i < l2 && i < m; ++i)
        q.push(b[i]);
    int p = 0;
    for (int i = l1; i < n && p < l3; ++i, ++p)
        q.push(c[p]);
    for (int i = l2; i < m && p < l3; ++i, ++p)
        q.push(c[p]);
    while (p < l3 && q.top() < c[p])
    {
        q.pop();
        q.push(c[p]);
        ++p;
    }

    long long ans = 0;
    while (!q.empty())
    {
        ans += q.top(); 
        q.pop();    
    }
    cout << ans << endl;
    return 0;
}