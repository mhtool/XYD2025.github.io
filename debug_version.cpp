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
    
    // cerr << "初始：n=" << n << ", mnn=" << mnn << endl;
    
    for(int i = 0; i < n; i++){
        char opt;
        ll k;
        cin >> opt >> k;
        
        // cerr << "操作 " << (i+1) << ": " << opt << " " << k << endl;
        
        if(opt == 'I'){
            ll actualSalary = k;
            if(actualSalary >= mnn){
                ll relativeSalary = k - adder;
                salaries.insert(relativeSalary);
                // cerr << "  录用员工，实际工资:" << actualSalary << ", 相对工资:" << relativeSalary << endl;
            }else{
                // cerr << "  员工工资" << actualSalary << "低于最低标准" << mnn << "，不录用" << endl;
            }
        }else if(opt == 'A'){
            adder += k;
            // cerr << "  全体加工资" << k << ", 当前adder=" << adder << endl;
        }else if(opt == 'S'){
            adder -= k;
            ll threshold = mnn - adder;
            
            auto it = salaries.lower_bound(threshold);
            ll leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            
            // cerr << "  全体减工资" << k << ", adder=" << adder << ", threshold=" << threshold;
            // cerr << ", 离职人数=" << leavingCount << endl;
            
            if(leavingCount > 0){
                salaries.erase(salaries.begin(), it);
            }
            
        }else if(opt == 'F'){
            ll totalEmployees = (ll)salaries.size();
            
            // cerr << "  查询第" << k << "高工资，当前员工数=" << totalEmployees << endl;
            
            if(k <= 0 || k > totalEmployees){
                cout << -1 << "\n";
                // cerr << "  输出: -1" << endl;
            }else{
                auto it = salaries.rbegin();
                advance(it, k - 1);
                ll actualSalary = *it + adder;
                cout << actualSalary << "\n";
                // cerr << "  输出: " << actualSalary << " (相对工资:" << *it << " + adder:" << adder << ")" << endl;
            }
        }
        
        // 调试：显示当前状态
        // cerr << "  当前员工相对工资: ";
        // for(auto x : salaries) cerr << x << " ";
        // cerr << ", 总离职数: " << goman << endl;
    }
    
    cout << goman << "\n";
    return 0;
}