#include<bits/stdc++.h>
using namespace std;
const int OFFSET=100000;
const int mxp=200001;
template<class T>
class linetree{
private:
    struct LT{
        T L, R, Value, add;
    };
    vector<LT> Linetree;
    int size;
    T merge(T left, T right){
        return left+right;
    }
    void apply_add(int u,T val){
        Linetree[u].Value=Linetree[u].Value+val*(Linetree[u].R-Linetree[u].L+1);
        Linetree[u].add=Linetree[u].add+val;
    }
    
public:
    linetree(int Length){
        this->size=Length;
        this->Linetree.resize(Length*4+10);
    }
    void pushUp(int Subscript){
        Linetree[Subscript].Value=merge(Linetree[Subscript<<1].Value,Linetree[Subscript<<1|1].Value);
    }
    void pushDown(int u){
        auto &root=Linetree[u], &left=Linetree[u<<1], &right=Linetree[u<<1|1];
        if(root.add){
            apply_add(u<<1,root.add);
            apply_add(u<<1|1,root.add);
            root.add=0;
        }
    }
    void build(int SubScript, int Left, int Right){
        if(Left==Right)
            Linetree[SubScript]={Left, Right, 0, 0};
        else{
            Linetree[SubScript]={Left, Right, 0, 0};
            int mid=(Left+Right) >> 1;
            build(SubScript<<1, Left, mid);
            build(SubScript<<1|1, mid+1, Right);
            pushUp(SubScript);
        }
    }
    T query(int Subscript, int Left, int Right){
        if(Left <= Linetree[Subscript].L&&Linetree[Subscript].R <= Right)
            return Linetree[Subscript].Value;
        pushDown(Subscript);
        int mid=(Linetree[Subscript].L+Linetree[Subscript].R) >> 1;
        T res=0;
        if(Left <= mid) res=query(Subscript<<1, Left, Right);
        if(Right > mid) res=merge(res, query(Subscript<<1|1, Left, Right));
        return res;
    }
    void point_add(int Subscript, int pos, T val){
        if(Linetree[Subscript].L==Linetree[Subscript].R){
            Linetree[Subscript].Value += val;
            return;
        }
        pushDown(Subscript);
        int mid=(Linetree[Subscript].L+Linetree[Subscript].R) >> 1;
        if(pos <= mid) point_add(Subscript<<1, pos, val);
        else point_add(Subscript<<1|1, pos, val);
        pushUp(Subscript);
    }
    int findKthLargest(int Subscript, int k){
        if(Linetree[Subscript].L==Linetree[Subscript].R){
            return Linetree[Subscript].L;
        }
        pushDown(Subscript);
        int rightCount=Linetree[Subscript<<1|1].Value;
        if(rightCount >= k)
            return findKthLargest(Subscript<<1|1, k);
        else
            return findKthLargest(Subscript<<1, k-rightCount);
    }
    T getTotalCount(){
        return Linetree[1].Value;
    }
    void clear(){
        fill(Linetree.begin(), Linetree.end(), LT{0, 0, 0, 0});
    }
};
int n,mnn,adder,goman;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>mnn;
    linetree<int>tr(mxp);
    tr.build(1,0,mxp-1);
    for(int i=1,k;i<=n;i++){
        char opt;
        cin>>opt>>k;
        if(opt=='I'){
            if(k>=mnn){
                int d=k-adder;
                int pos=d+OFFSET;
                if(pos>=0&&pos<mxp)
                    tr.point_add(1, pos, 1);
            }
        }else if(opt=='A'){
            adder+=k;
        }else if(opt=='S'){
            adder-=k;
            int go=mnn-adder+OFFSET;
            if(go > 0){  // 修复：改为 go > 0
                int gocnt=tr.query(1,0,min(go-1,mxp-1));
                goman+=gocnt;
                vector<pair<int,int>>tmp;
                for(int j=max(0,go),cnt;j<mxp;j++){
                    cnt=tr.query(1,j,j);
                    if(cnt)
                        tmp.push_back({j,cnt});
                }
                tr.clear();
                tr.build(1,0,mxp-1);
                for(auto&p:tmp)
                    tr.point_add(1,p.first,p.second);
            }
        }else if(opt=='F'){
            int len=tr.getTotalCount();
            if(k>len)
                cout<<-1<<"\n";
            else{
                int pos=tr.findKthLargest(1,k);
                cout<<pos-OFFSET+adder<<"\n";
            }
        }
    }
    cout<<goman<<"\n";
    return 0;
}