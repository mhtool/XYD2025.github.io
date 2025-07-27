#include <bits/stdc++.h>
using namespace std;
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    int now = 0;
    for (char c : s)
        now = (now + c - '0') % 3;
    if (now == 0)
        cout << "Yes\n";
    else 
        cout << "No\n";
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}