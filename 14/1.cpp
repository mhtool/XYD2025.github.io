#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' +  s + '#' + string(s.rbegin(), s.rend());
    vector<int> pi(s.size());
    for (int i = 2; i < s.size(); ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && s[len + 1] != s[i])
            len = pi[len];
        if (s[len + 1] == s[i])
            ++len;
        pi[i] = len;
    }
    vector<int> pos;
    vector<int> ans(n + 1);
    int border = pi[s.size() - 1];
    while (border > 0)
    {
        pos.push_back(border);
        border = pi[border];
    }
    reverse(pos.begin(), pos.end());
    long long res = 0;
    for (int x : pos)
        ans[x] = ans[x / 2] + 1;
    res = accumulate(ans.begin(), ans.end(), 0LL);
    cout << res << endl;
}


/*

C C e C e C C C e e # e e C C C e C e C C
0 1 0 1 0 1 2 2 3 0 0 0 0 1 2 2 3 4 5 6 7


*/