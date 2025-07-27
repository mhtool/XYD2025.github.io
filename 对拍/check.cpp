#include <bits/stdc++.h>
using namespace std;
int main()
{
    int times = 0;
    do
    {
        cout << "times = " << times << endl;
        system("./data > data.in");
        system("./correct < data.in > correct.out");
        system("./mine < data.in > mine.out");
        ++times;
    } while(system("diff mine.out correct.out")==0);
}