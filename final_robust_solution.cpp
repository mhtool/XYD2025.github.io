#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    ll mnn;
    cin >> n >> mnn;
    
    multiset<ll> salaries; 
    ll adder = 0; 
    ll goman = 0; 
    
    for(int i = 0; i < n; i++){
        char opt;
        ll k;
        cin >> opt >> k;
        
        if(opt == 'I'){
            // 插入新员工：只有当前实际工资不低于最低标准才录用
            ll actualSalary = k;
            if(actualSalary >= mnn){
                ll relativeSalary = k - adder;
                salaries.insert(relativeSalary);
            }
            // 注意：初始工资低于最低标准的员工不录用，不计入离职统计
        }else if(opt == 'A'){
            // 全体加工资
            adder += k;
        }else if(opt == 'S'){
            // 全体减工资
            adder -= k;
            
            // 计算阈值：相对工资需要达到多少才能满足最低标准
            ll threshold = mnn - adder;
            
            // 找到第一个相对工资不小于threshold的员工
            auto it = salaries.lower_bound(threshold);
            
            // 计算需要删除的员工数量（相对工资小于threshold的）
            ll leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            
            // 删除这些员工
            if(leavingCount > 0){
                salaries.erase(salaries.begin(), it);
            }
            
        }else if(opt == 'F'){
            // 查询第k高工资
            ll totalEmployees = (ll)salaries.size();
            
            if(k <= 0 || k > totalEmployees){
                cout << -1 << "\n";
            }else{
                // multiset从小到大排序，要找第k高需要从右边数第k个
                auto it = salaries.rbegin();
                advance(it, k - 1);
                
                // 计算实际工资 = 相对工资 + 全局调整
                ll actualSalary = *it + adder;
                cout << actualSalary << "\n";
            }
        }
    }
    
    cout << goman << "\n";
    return 0;
}

/*
处理的hack情况：

1. 数据范围问题
   - 使用long long防止溢出
   - 处理极大的工资数值

2. 边界情况
   - k <= 0 的F查询
   - 空员工集合的F查询  
   - n = 0的情况

3. 逻辑漏洞
   - 确保I操作只录用合格员工
   - 正确计算S操作的离职人数
   - 准确处理相对工资和实际工资的转换

4. 特殊序列
   - 连续的大幅度S操作
   - 工资调整导致负工资的情况
   - 混合的A/S操作序列

5. 精度问题
   - 所有计算使用long long
   - 避免中间结果溢出
*/