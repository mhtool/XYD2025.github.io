#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    string t;
    cin >> n >> t;
    vector<string> s(n);
    for (int i = 0; i < n; ++i)
        cin >> s[i];

    vector<int> str(1);
    str.insert(str.end(), t.begin(), t.end());
    for (int i = 0; i < n; ++i)
        str.push_back(-i - 1),
        str.insert(str.end(), s[i].begin(), s[i].end());

    int id = -1;
    vector<int> ids;
    vector<int> pi(str.size());
    
    for (int i = 2; i < str.size(); ++i)
    {
        int len = pi[i - 1];
        while (len > 0 && str[len + 1] != str[i])
            len = pi[len];
        if (str[len + 1] == str[i])
            ++len;
        if (str[i] < 0)
            ++id;
        pi[i] = len;
        if (pi[i] == t.size() && (ids.empty() || ids.back() != id))
            ids.push_back(id);
    }
    sort(ids.begin(), ids.end(), [&](int a, int b)
         { return s[a] < s[b]; });
    for (int x : ids)
        cout << s[x] << endl;

}

/*
a b a b a b
0 0 1 2 3 4


*/