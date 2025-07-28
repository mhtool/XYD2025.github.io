#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, minSalary;
    cin >> n >> minSalary;
    
    multiset<int> salaries; // 存储所有员工的相对工资
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
                salaries.insert(relativeSalary);
            }
        } else if (op == 'A') {
            // 全体加工资
            globalAdd += k;
        } else if (op == 'S') {
            // 全体减工资
            globalAdd -= k;
            
            // 移除工资低于最低标准的员工
            int threshold = minSalary - globalAdd;
            
            auto it = salaries.lower_bound(threshold);
            int leavingCount = distance(salaries.begin(), it);
            leftCount += leavingCount;
            salaries.erase(salaries.begin(), it);
        } else if (op == 'F') {
            // 查询第k高工资
            if (k > salaries.size()) {
                cout << -1 << "\n";
            } else {
                // 找第k高工资（从大到小排序的第k个）
                auto it = salaries.rbegin();
                advance(it, k - 1);
                int actualSalary = *it + globalAdd;
                cout << actualSalary << "\n";
            }
        }
    }
    
    cout << leftCount << "\n";
    
    return 0;
}