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
            if(k >= mnn){
                int relativeSalary = k - adder;
                salaries.insert(relativeSalary);
            }
        }else if(opt == 'A'){
            adder += k;
        }else if(opt == 'S'){
            adder -= k;
            
            int threshold = mnn - adder;
            auto it = salaries.lower_bound(threshold);
            int leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            salaries.erase(salaries.begin(), it);
        }else if(opt == 'F'){
            if(k > (int)salaries.size()){
                cout << -1 << "\n";
            }else{
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