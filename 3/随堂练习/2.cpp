#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int ans = n;
    for (char c = 'a'; c <= 'z'; ++c)
    {
        int i = 0;
        int res = 0;
        while (i < s.size())
        {
            if (s[i] == c)
                ++i;
            else
                i += m, ++res;
        }
        ans = min(ans, res);
    }
    cout << ans << endl;
}