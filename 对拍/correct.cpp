#include<bits/stdc++.h>

typedef long long ll;
const int MAXN = 5000011,mod1 = 998244353,mod2 = 1e9+7,base = 131;
struct hash
{
    int x,y;
    hash(){}
    hash(int _x,int _y){x=_x,y=_y;}
    hash operator+ (hash you){return hash((x+you.x)%mod1,(y+you.y)%mod2);}
    hash operator- (hash you)
    {
        int vx=x-you.x,vy=y-you.y;
        if(vx<0)vx+=mod1;
        if(vy<0)vy+=mod2;
        return hash(vx,vy);
    }
    hash operator* (hash you){return hash((ll)x*you.x%mod1,(ll)y*you.y%mod2);}
    bool operator== (hash you){return x==you.x&&y==you.y;}
    void see(){printf("%d %d\n",x,y);}
};
hash f[MAXN],rf[MAXN],pw[MAXN];
hash get1(int l,int r){return f[r]-f[l-1]*pw[r-l+1];}
hash get2(int l,int r){return rf[l]-rf[r+1]*pw[r-l+1];}
char s[MAXN];
int res[MAXN];
int main()
{
    int n;
    scanf("%s",s+1);
    n=strlen(s+1);
    pw[0]=hash(1,1);
    for(int i=1;i<=n;++i)pw[i]=pw[i-1]*hash(base,base);
    f[0]=hash(0,0);
    for(int i=1;i<=n;++i)f[i]=f[i-1]*hash(base,base)+hash(s[i],s[i]);
    for(int i=n;i;--i)rf[i]=rf[i+1]*hash(base,base)+hash(s[i],s[i]);
    ll ans=0;
    for(int i=1;i<=n;++i)
    {
        if(get1(1,i)==get2(1,i))res[i]=res[i>>1]+1;
        else res[i]=0;
        //printf("res=%d\n",res[i]);
        printf("%d ",res[i]);
        ans+=res[i];
    }
    puts("");
    printf("%lld\n",ans);
    return 0;
}