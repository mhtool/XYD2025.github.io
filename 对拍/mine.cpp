#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    vector<int> pi(n + 1);
    vector<int> ans(n + 1);
    long long res = 0;
    for (int i = 1; i <= n; ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && s[len + 1] != s[i])
            len = pi[len];
        if (s[len + 1] == s[i] && len + 1 <= i / 2)
            ++len;
        pi[i] = len;
        if (pi[i] == i / 2)
            ans[i] = ans[i / 2] + 1;
        res += ans[i];
    }
    for (int i = 1; i <= n; ++i)
        cout << pi[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";
    cout << "\n";
    cout << res << endl;
}


/*
aaaaa

i = 2 len <= 1
i = 3 len <= 2;
*/