#include <bits/stdc++.h>
using namespace std;
int main()
{
    int q;
    cin >> q;
    const int M = 1e6 + 5;
    vector<int> cnt(M);
    int num = 0;
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x;
            cin >> x;
            if (cnt[x] == 0)
                ++num;
            ++cnt[x];
        }
        else if (op == 2)
        {
            int x;
            cin >> x;
            if (cnt[x] > 0)
            {
                --cnt[x];
                if (cnt[x] == 0)
                    --num;
            }
        }
        else
        {
            cout << num << endl;
        }
    }
}