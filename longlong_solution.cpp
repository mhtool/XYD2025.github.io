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
    
    for(int i = 1; i <= n; i++){
        char opt;
        ll k;
        cin >> opt >> k;
        
        if(opt == 'I'){
            if(k >= mnn){
                ll relativeSalary = k - adder;
                salaries.insert(relativeSalary);
            }
        }else if(opt == 'A'){
            adder += k;
        }else if(opt == 'S'){
            adder -= k;
            
            ll threshold = mnn - adder;
            auto it = salaries.lower_bound(threshold);
            ll leavingCount = distance(salaries.begin(), it);
            goman += leavingCount;
            salaries.erase(salaries.begin(), it);
            
        }else if(opt == 'F'){
            ll totalEmployees = salaries.size();
            
            if(k > totalEmployees || totalEmployees == 0){
                cout << -1 << "\n";
            }else{
                auto it = salaries.rbegin();
                advance(it, k - 1);
                ll actualSalary = *it + adder;
                cout << actualSalary << "\n";
            }
        }
    }
    
    cout << goman << "\n";
    return 0;
}