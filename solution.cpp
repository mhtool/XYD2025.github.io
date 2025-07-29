#include <iostream>
#include <vector>
#include <algorithm>
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
    
    long long moves = 0;
    int current_pos = 0;
    
    for (int i = 0; i < n; i++) {
        int obstacle_pos = x[i];
        int target_pos = obstacle_pos - 1; // Position we need to reach to jump over obstacle
        
        if (target_pos < current_pos) {
            // Can't reach this position
            cout << -1 << endl;
            return 0;
        }
        
        // Calculate minimum moves to reach target_pos from current_pos
        int distance = target_pos - current_pos;
        
        // Optimal way: use as many jumps (2 steps) as possible, then walks (1 step)
        long long jumps = distance / 2;
        long long walks = distance % 2;
        
        moves += jumps + walks; // Total moves to reach target_pos
        moves += 1; // Jump over the obstacle
        
        // Update current position after jumping over obstacle
        current_pos = obstacle_pos + 1;
    }
    
    cout << moves << endl;
    return 0;
}