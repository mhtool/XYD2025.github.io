#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
string s,ss;
long long base=233,mod=1e9+7;
long long ans=0;
int main(){
	cin>>s;
	ss=s;
	reverse(ss.begin(),ss.end());
	
  int l=s.size();
	vector<long long>hash1(l+5,0),hash2(l+5,0),dp(l+5,0);

	for(int i=1;i<=l;i++){
		hash1[i]=(hash1[i-1]*base+(s[i-1]-'a')+mod)%mod;
		hash2[i]=(hash2[i-1]*base+(ss[i-1]-'a')+mod)%mod;
	}
	vector<long long>pw(l+5,0);
	pw[0]=1;

	for(int i=1;i<=l;i++)
		pw[i]=pw[i-1]*base%mod;

	for(int i=1;i<=l;i++){
		if(hash1[i]==(hash2[l]-hash2[l-i]*pw[i]%mod+mod)%mod)
			dp[i]=dp[i/2]+1;
		ans+=dp[i];
	}
	cout<<ans;
	
	return 0;
}


