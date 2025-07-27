#include <bits/stdc++.h>
using namespace std;

void kmp_1_index(string s)
{
    int n = s.size();
    s = " " + s;
    vector<int> pi(n + 1);
    int ans = 0;
    for (int i = 2; i <= n; ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && s[len + 1] != s[i])
            len = pi[len];
        if (s[len + 1] == s[i])
            ++len;
        pi[i] = len;
    }
    int border = pi[n];
    int ans = n;
    while (border > 0)
    {
        int period = n - border;
        if (n % period == 0)
        {
            ans = period;
            break;
        }
        border = pi[border];
    }
    cout << ans << endl;
}
int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    kmp_1_index(t);
}