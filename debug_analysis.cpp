// 分析您原代码中可能的WA原因：

/*
问题1: #define int long long 可能导致的问题
- findKthLargest返回int，但模板参数T也是int(long long)
- 可能在大数处理上有问题

问题2: S操作的边界条件
if(go>0){ // 这里可能有问题
    // 当go=0时不执行删除，但实际上go=0也可能需要删除员工
}

问题3: 清空和重建的问题
tr.clear(); // 可能没有正确清空所有状态
tr.build(1,0,mxp-1); // 重建可能有状态残留

问题4: 查询边界
for(int j=max(0ll,go),cnt;j<mxp;j++){
    // max(0ll,go) 这里用了0ll，但go是int(long long)
}

问题5: findKthLargest的返回值类型不一致
int findKthLargest(int Subscript, int k){ // 返回int
    // 但是所有其他地方都用的T类型
}
*/

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
        if(Left > Right) return 0;  // 添加边界检查
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
    T findKthLargest(int Subscript, int k){  // 修复：返回T类型
        if(Linetree[Subscript].L==Linetree[Subscript].R){
            return Linetree[Subscript].L;
        }
        pushDown(Subscript);
        T rightCount=Linetree[Subscript<<1|1].Value;
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
            // 修复：即使go=0也要检查是否有员工需要删除
            if(go > 0 && go <= mxp){  // 添加上界检查
                int gocnt=tr.query(1,0,go-1);
                goman+=gocnt;
                if(gocnt > 0){  // 只有真的有员工离职才重建
                    vector<pair<int,int>>tmp;
                    for(int j=go; j<mxp; j++){
                        int cnt=tr.query(1,j,j);
                        if(cnt > 0)
                            tmp.push_back({j,cnt});
                    }
                    tr.clear();
                    tr.build(1,0,mxp-1);
                    for(auto&p:tmp)
                        tr.point_add(1,p.first,p.second);
                }
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