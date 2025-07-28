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
            
            // 优化：避免使用distance，直接计数删除
            int leavingCount = 0;
            auto it = salaries.begin();
            while(it != salaries.end() && *it < threshold){
                ++leavingCount;
                it = salaries.erase(it);
            }
            goman += leavingCount;
            
        }else if(opt == 'F'){
            if(k > (int)salaries.size()){
                cout << -1 << '\n';
            }else{
                // 优化：使用vector临时存储避免反向迭代器
                vector<int> temp(salaries.rbegin(), salaries.rend());
                cout << temp[k-1] + adder << '\n';
            }
        }
    }
    
    cout << goman << '\n';
    return 0;
}