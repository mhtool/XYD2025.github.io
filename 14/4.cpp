#include <bits/stdc++.h>
using namespace std;

void kmp_1_index(string s)
{
    int n = s.size();
    s = " " + s;
    vector<int> pi(n + 1);
    for (int i = 2; i <= n; ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && s[len + 1] != s[i])
            len = pi[len];
        if (s[len + 1] == s[i])
            ++len;
        pi[i] = len;
    }
    auto min_border = pi;
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int &len = min_border[i];
        while (len > 0 && min_border[len] > 0)
            len = min_border[len];
        if (len == 0)
            ans += 233;
        else 
            ans += i - len;
    }
    cout << ans << endl;
}
int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    kmp_1_index(s);
}