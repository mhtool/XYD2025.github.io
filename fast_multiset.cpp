#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, mnn;
    cin >> n >> mnn;
    
    multiset<int> salaries; 
    int adder = 0; 
    int goman = 0; 
    
    salaries.reserve(100000); // 预分配空间
    
    for(int i = 0; i < n; i++){
        char opt;
        int k;
        cin >> opt >> k;
        
        if(opt == 'I'){
            if(k >= mnn){
                salaries.insert(k - adder);
            }
        }else if(opt == 'A'){
            adder += k;
        }else if(opt == 'S'){
            adder -= k;
            
            int threshold = mnn - adder;
            auto it = salaries.lower_bound(threshold);
            int leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            
            // 优化：使用单次erase避免多次调用
            if(leavingCount > 0){
                salaries.erase(salaries.begin(), it);
            }
            
        }else if(opt == 'F'){
            int sz = salaries.size();
            if(k > sz){
                cout << -1 << '\n';
            }else{
                auto it = salaries.end();
                advance(it, -k);  // 从end向前移动k步
                cout << *it + adder << '\n';
            }
        }
    }
    
    cout << goman << '\n';
    return 0;
}