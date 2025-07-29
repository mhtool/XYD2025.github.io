#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    // Check if consecutive obstacles exist
    for (int i = 0; i < n - 1; i++) {
        if (x[i+1] - x[i] == 1) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    // Find the furthest position we need to reach
    int max_pos = x[n-1] + 1;
    
    // dp[pos] = minimum moves to reach position pos
    vector<long long> dp(max_pos + 3, LLONG_MAX);
    dp[0] = 0;
    
    // Mark obstacle positions
    vector<bool> is_obstacle(max_pos + 3, false);
    for (int i = 0; i < n; i++) {
        is_obstacle[x[i]] = true;
    }
    
    for (int pos = 0; pos <= max_pos; pos++) {
        if (dp[pos] == LLONG_MAX) continue;
        
        // Don't stay on obstacle
        if (is_obstacle[pos]) continue;
        
        // Walk 1 step
        if (pos + 1 <= max_pos + 2 && !is_obstacle[pos + 1]) {
            dp[pos + 1] = min(dp[pos + 1], dp[pos] + 1);
        }
        
        // Jump 2 steps
        if (pos + 2 <= max_pos + 2) {
            dp[pos + 2] = min(dp[pos + 2], dp[pos] + 1);
        }
    }
    
    // Check if we can reach position after each obstacle
    for (int i = 0; i < n; i++) {
        if (dp[x[i] + 1] == LLONG_MAX) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    // The answer is the minimum moves to reach the position after the last obstacle
    cout << dp[x[n-1] + 1] << endl;
    return 0;
}