#include <bits/stdc++.h>
using namespace std;
int main()
{

    int n = 10;
    for (int i = 1; i <= n; ++i)
        cout << char(rand() % 2 + 'a');
    cout << "\n";
}