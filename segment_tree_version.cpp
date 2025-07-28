/*
 * P1486 [NOI2004] 忧郁的出纳员 - 线段树解法
 * 
 * 核心思想：
 * 1. 使用全局偏移量globalAdd来处理全体加工资/减工资操作
 * 2. 将员工工资转换为相对工资存储在线段树中
 * 3. 支持查询第k高工资和快速删除低于最低标准的员工
 * 
 * 时间复杂度：O(n log max_salary)
 * 空间复杂度：O(max_salary)
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int OFFSET = 100000;
const int RANGE = 200001;

struct SegmentTree {
    vector<int> tree;
    int n;
    
    SegmentTree() {
        n = 1;
        while (n < RANGE) n *= 2;
        tree.assign(2 * n, 0);
    }
    
    void update(int pos, int val) {
        if (pos < 0 || pos >= RANGE) return;
        pos += n;
        tree[pos] += val;
        while (pos > 1) {
            pos /= 2;
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        }
    }
    
    int query(int l, int r) {
        if (l > r || l < 0 || r >= RANGE) return 0;
        l = max(0, l);
        r = min(RANGE - 1, r);
        l += n;
        r += n;
        int res = 0;
        while (l <= r) {
            if (l % 2 == 1) res += tree[l++];
            if (r % 2 == 0) res += tree[r--];
            l /= 2;
            r /= 2;
        }
        return res;
    }
    
    // 找第k大的位置（从大到小排序的第k个）
    int findKthLargest(int k) {
        if (k <= 0 || tree[1] < k) return -1;
        int pos = 1;
        while (pos < n) {
            int rightCount = tree[2 * pos + 1];
            if (rightCount >= k) {
                pos = 2 * pos + 1;
            } else {
                k -= rightCount;
                pos = 2 * pos;
            }
        }
        return pos - n;
    }
    
    int getTotalCount() {
        return tree[1];
    }
    
    void clear() {
        fill(tree.begin(), tree.end(), 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, minSalary;
    cin >> n >> minSalary;
    
    SegmentTree st;
    int globalAdd = 0; // 全局工资调整量
    int leftCount = 0; // 离职员工数
    
    for (int i = 0; i < n; i++) {
        char op;
        int k;
        cin >> op >> k;
        
        if (op == 'I') {
            // 插入新员工
            if (k >= minSalary) {
                int relativeSalary = k - globalAdd; // 相对于当前基准的工资
                int pos = relativeSalary + OFFSET;
                st.update(pos, 1);
            }
        } else if (op == 'A') {
            // 全体加工资
            globalAdd += k;
        } else if (op == 'S') {
            // 全体减工资
            globalAdd -= k;
            
            // 移除工资低于最低标准的员工
            int threshold = minSalary - globalAdd + OFFSET;
            if (threshold > 0) {
                int leavingCount = st.query(0, threshold - 1);
                leftCount += leavingCount;
                
                // 重建线段树，只保留工资不低于最低标准的员工
                vector<pair<int, int>> remaining; // {position, count}
                for (int j = threshold; j < RANGE; j++) {
                    int count = st.query(j, j);
                    if (count > 0) {
                        remaining.push_back({j, count});
                    }
                }
                
                st.clear();
                for (auto& p : remaining) {
                    st.update(p.first, p.second);
                }
            }
        } else if (op == 'F') {
            // 查询第k高工资
            int totalEmployees = st.getTotalCount();
            if (k > totalEmployees) {
                cout << -1 << "\n";
            } else {
                // 找第k高工资
                int pos = st.findKthLargest(k);
                if (pos != -1) {
                    int actualSalary = pos - OFFSET + globalAdd;
                    cout << actualSalary << "\n";
                } else {
                    cout << -1 << "\n";
                }
            }
        }
    }
    
    cout << leftCount << "\n";
    
    return 0;
}