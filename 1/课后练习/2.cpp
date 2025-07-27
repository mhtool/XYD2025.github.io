#include <bits/stdc++.h>
using namespace std;
vector<string> dfs(int level)
{
    if (level == 1)
    {
        return vector<string>({
            " /\\ ",
            "/__\\",
        });
    }
    vector<string> prev = dfs(level - 1);
    vector<string> upper(prev.size()); // 上层的图形
    vector<string> lower = prev; // 下层的图形
    string space(1 << (level - 1), ' '); // 计算当前层的空格数
    for (int i = 0; i < prev.size(); ++i)
    {
        upper[i] = space + prev[i];
    }
    for (int i = 0; i < lower.size(); ++i)
    {
        int num_spaces = (1 << (level - 1)) - 1 - i;
        if (num_spaces < 0) num_spaces = 0;
        lower[i] = lower[i] + string(num_spaces, ' ') + lower[i];
    }
    upper.insert(upper.end(), lower.begin(), lower.end());
    return upper;
}
int main()
{
    int n;
    string s1 = "134";
    string s2 = "144";
    string spaces = string(10, ' ');
    cin >> n;
    vector<string> result = dfs(n);
    for (const string &line : result)
    {
        cout << line << endl;
    }
    return 0;
}