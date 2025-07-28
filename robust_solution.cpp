#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, mnn;
    cin >> n >> mnn;
    
    multiset<int> salaries; 
    int adder = 0; 
    int goman = 0; 
    
    for(int i = 1; i <= n; i++){
        char opt;
        int k;
        cin >> opt >> k;
        
        if(opt == 'I'){
            // 插入新员工：只有初始工资不低于最低标准才录用
            if(k >= mnn){
                int relativeSalary = k - adder;
                salaries.insert(relativeSalary);
            }
            // 注意：工资低于最低标准的不算离职员工
        }else if(opt == 'A'){
            // 全体加工资
            adder += k;
        }else if(opt == 'S'){
            // 全体减工资
            adder -= k;
            
            // 删除工资低于最低标准的员工
            int threshold = mnn - adder;
            
            // 找到第一个不小于threshold的位置
            auto it = salaries.lower_bound(threshold);
            
            // 计算需要删除的员工数量
            int leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            
            // 删除这些员工
            salaries.erase(salaries.begin(), it);
            
        }else if(opt == 'F'){
            // 查询第k高工资
            int totalEmployees = salaries.size();
            
            if(k > totalEmployees || totalEmployees == 0){
                cout << -1 << "\n";
            }else{
                // multiset默认从小到大排序
                // 要找第k高，需要从右边数第k个
                auto it = salaries.rbegin();
                advance(it, k - 1);
                
                // 计算实际工资
                int actualSalary = *it + adder;
                cout << actualSalary << "\n";
            }
        }
    }
    
    cout << goman << "\n";
    return 0;
}

/*
可能的hack点分析：

1. 极端的工资调整
   - 大量S操作导致所有员工离职
   - 工资调整超出int范围

2. 边界情况
   - n=0（无操作）
   - 所有I操作的工资都低于最低标准
   - F操作查询不存在的排名

3. 精度问题
   - 使用long long可能在某些情况下更安全

4. 特殊序列
   - 先大量I，再大量S删除所有人，再F查询
   - 交替的A和S操作

修复建议：
- 确保所有边界条件都正确处理
- 考虑使用long long防止溢出
- 仔细处理空集合的情况
*/