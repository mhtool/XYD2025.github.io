#include <bits/stdc++.h>
using namespace std;

void kmp_0_index(string s, string t)
{
    int n = s.size(), m = t.size();
    string str = s + '#' + t;
    int tot = n + m + 1;
    vector<int> pi(tot);
    for (int i = 1; i < tot; ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && str[len] != str[i])
            len = pi[len - 1];
        if (str[len] == str[i])
            ++len;
        pi[i] = len;
        if (pi[i] == n)
            cout << i - 2 * n << " ";
    }
    cout << "\n";
}

void kmp_1_index(string s, string t)
{
    string str = " " + s + '#' + t;
    int n = s.size(), m = t.size();
    int tot = n + m + 2;
    vector<int> pi(tot);
    for (int i = 2; i < tot; ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && str[len + 1] != str[i])
            len = pi[len];
        if (str[len + 1] == str[i])
            ++len;
        pi[i] = len;
        if (pi[i] == n)
            cout << i - 2 * n - 1 << " ";
    }
    cout << "\n";
}
int main()
{
    string s, t;
    cin >> s >> t;
    kmp_0_index(s, t);
    kmp_1_index(s, t);
}