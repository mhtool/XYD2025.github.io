#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

// Dijkstra算法求最短路径
vector<vector<int>> dijkstra(int sx, int sy, vector<vector<int>>& mat) {
    int n = mat.size() - 1;
    int m = mat[0].size() - 1;
    
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INT_MAX));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    
    const int dx[] = {0, 0, 1, -1};
    const int dy[] = {1, -1, 0, 0};
    
    dist[sx][sy] = 0;
    pq.push({0, {sx, sy}});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();
        
        if (d > dist[x][y]) continue;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                int height_diff = abs(mat[x][y] - mat[nx][ny]);
                int cost = height_diff * height_diff + 1;
                
                if (dist[x][y] + cost < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + cost;
                    pq.push({dist[nx][ny], {nx, ny}});
                }
            }
        }
    }
    
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> mat(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }
    
    int p;
    cin >> p;
    
    vector<Point> points(p + 1);
    points[0] = {1, 1}; // 起点
    
    for (int i = 1; i <= p; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    // 计算所有点对之间的最短距离
    vector<vector<int>> graph(p + 1, vector<int>(p + 1, INT_MAX));
    
    for (int i = 0; i <= p; i++) {
        auto dist = dijkstra(points[i].x, points[i].y, mat);
        
        for (int j = 0; j <= p; j++) {
            if (i != j) {
                graph[i][j] = dist[points[j].x][points[j].y];
            }
        }
    }
    
    // 状态压缩DP求TSP
    vector<vector<int>> dp(1 << (p + 1), vector<int>(p + 1, INT_MAX));
    dp[1][0] = 0; // 从起点0开始，状态为只访问了起点
    
    for (int mask = 0; mask < (1 << (p + 1)); mask++) {
        for (int u = 0; u <= p; u++) {
            if (dp[mask][u] == INT_MAX) continue;
            if (!(mask & (1 << u))) continue;
            
            for (int v = 1; v <= p; v++) { // 只考虑景点，不回到起点
                if (mask & (1 << v)) continue;
                if (graph[u][v] == INT_MAX) continue;
                
                int new_mask = mask | (1 << v);
                dp[new_mask][v] = min(dp[new_mask][v], dp[mask][u] + graph[u][v]);
            }
        }
    }
    
    // 找到访问所有景点的最小时间
    int full_mask = (1 << (p + 1)) - 1; // 所有点都访问过
    int ans = INT_MAX;
    
    for (int i = 1; i <= p; i++) {
        ans = min(ans, dp[full_mask][i]);
    }
    
    cout << ans << endl;
    
    return 0;
}