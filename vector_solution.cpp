#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, mnn;
    cin >> n >> mnn;
    
    vector<int> salaries; 
    salaries.reserve(100000);
    int adder = 0; 
    int goman = 0; 
    
    for(int i = 0; i < n; i++){
        char opt;
        int k;
        cin >> opt >> k;
        
        if(opt == 'I'){
            if(k >= mnn){
                salaries.push_back(k - adder);
            }
        }else if(opt == 'A'){
            adder += k;
        }else if(opt == 'S'){
            adder -= k;
            
            int threshold = mnn - adder;
            
            // 移除所有小于threshold的元素
            int leavingCount = 0;
            vector<int> remaining;
            remaining.reserve(salaries.size());
            
            for(int salary : salaries){
                if(salary < threshold){
                    leavingCount++;
                }else{
                    remaining.push_back(salary);
                }
            }
            
            goman += leavingCount;
            salaries = move(remaining);
            
        }else if(opt == 'F'){
            if(k > (int)salaries.size()){
                cout << -1 << '\n';
            }else{
                // 部分排序，只排序前k个最大元素
                nth_element(salaries.begin(), salaries.begin() + salaries.size() - k, salaries.end());
                cout << salaries[salaries.size() - k] + adder << '\n';
            }
        }
    }
    
    cout << goman << '\n';
    return 0;
}