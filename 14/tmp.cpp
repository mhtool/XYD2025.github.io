#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    string str = " " + s + "#" + t;
    // s[0] 1...n

    vector<int> pi(str.size());
    for (int i = 2; i < str.size(); ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && str[len + 1] != str[i])
            len = pi[len];
        if (str[len + 1] == str[i])
            ++len;
        pi[i] = len;
        if (pi[i] == n)
        {
            // i
            // i - n - 1
            // i - n 第一个位置 1-index
            cout << i - 2 * n << " ";
        }
    }
    cout << endl;
}