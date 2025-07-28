#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, mnn;
    cin >> n >> mnn;
    
    multiset<int> salaries; // 存储所有员工的相对工资
    int adder = 0; // 全局工资调整量
    int goman = 0; // 离职员工数
    
    for(int i = 1; i <= n; i++){
        char opt;
        int k;
        cin >> opt >> k;
        
        if(opt == 'I'){
            if(k >= mnn){
                int relativeSalary = k - adder; // 相对于当前基准的工资
                salaries.insert(relativeSalary);
            }
        }else if(opt == 'A'){
            adder += k;
        }else if(opt == 'S'){
            adder -= k;
            
            // 移除工资低于最低标准的员工
            int threshold = mnn - adder;
            auto it = salaries.lower_bound(threshold);
            int leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            salaries.erase(salaries.begin(), it);
        }else if(opt == 'F'){
            if(k > salaries.size()){
                cout << -1 << "\n";
            }else{
                // 找第k高工资（从大到小排序的第k个）
                auto it = salaries.rbegin();
                advance(it, k - 1);
                int actualSalary = *it + adder;
                cout << actualSalary << "\n";
            }
        }
    }
    
    cout << goman << "\n";
    return 0;
}