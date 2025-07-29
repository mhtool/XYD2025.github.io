#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Check consecutive obstacles
    for (int i = 0; i < n - 1; i++) {
        if (a[i+1] - a[i] == 1) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    long long ans = 0;
    int pos = 0;
    
    for (int i = 0; i < n; i++) {
        int need = a[i] - 1; // Position before obstacle
        
        if (need < pos) {
            cout << -1 << endl;
            return 0;
        }
        
        int dist = need - pos;
        ans += (dist + 1) / 2; // Minimum moves to reach need
        ans += 1; // Jump over obstacle
        
        pos = a[i] + 1; // Position after jumping
    }
    
    cout << ans << endl;
    return 0;
}