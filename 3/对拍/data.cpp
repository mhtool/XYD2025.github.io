#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("data.in", "w", stdout);
    srand(time(0));
    int n, m, x, y, z;
    while (1)
    {
        n = rand() % 5 + 1;
        m = rand() % 5 + 1;
        x = rand() % 5 + 1;
        y = rand() % 5 + 1;
        z = rand() % 5 + 1;
        if (n + m < x + y + z)
            break;
    }
    printf("%d %d %d %d %d\n", n, m, x, y, z);
    for (int i = 1; i <= x; ++i)
        cout << rand() % 10 + 1 << " ";
    cout << "\n";
    for (int i = 1; i <= y; ++i)
        cout << rand() % 10 + 1 << " ";
    cout << "\n";
    for (int i = 1; i <= z; ++i)
        cout << rand() % 10 + 1 << " ";
    cout << "\n";
}