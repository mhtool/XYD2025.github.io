/*
 * P1486 [NOI2004] 忧郁的出纳员 - 基于用户线段树模板的解法
 * 
 * 改动说明：
 * 1. 删除了乘法操作和模运算相关代码
 * 2. 添加了第k大查询功能
 * 3. 简化了merge函数为简单加法
 * 4. 添加了单点更新和清空功能
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int OFFSET = 100000;
const int RANGE = 200001;

template<class T>
class linetree {
private:
    struct LT {
        T L, R, Value, add;
    };
    vector<LT> Linetree;
    int size;
    
    T merge(T left, T right) {
        return left + right;  // 简化：直接加法，去掉模运算
    }
    
    void apply_add(int u, T val) {
        Linetree[u].Value = Linetree[u].Value + val * (Linetree[u].R - Linetree[u].L + 1);
        Linetree[u].add = Linetree[u].add + val;
    }
    
public:
    linetree(int Length) {
        this->size = Length;
        this->Linetree.resize(Length * 4 + 10);
    }
    
    void pushUp(int Subscript) {
        Linetree[Subscript].Value = merge(Linetree[Subscript<<1].Value, 
                                        Linetree[Subscript<<1|1].Value);
    }
    
    void pushDown(int u) {
        auto &root = Linetree[u], &left = Linetree[u<<1], &right = Linetree[u<<1|1];
        if(root.add) {
            apply_add(u<<1, root.add);
            apply_add(u<<1|1, root.add);
            root.add = 0;
        }
    }
    
    void build(T BuildArray[], int SubScript, int Left, int Right) {
        if(Left == Right) {
            Linetree[SubScript] = {Left, Right, BuildArray[Left], 0};
        } else {
            Linetree[SubScript] = {Left, Right, 0, 0};
            int mid = (Left + Right) >> 1;
            build(BuildArray, SubScript<<1, Left, mid);
            build(BuildArray, SubScript<<1|1, mid+1, Right);
            pushUp(SubScript);
        }
    }
    
    // 简化构建：全部初始化为0
    void build(int SubScript, int Left, int Right) {
        if(Left == Right) {
            Linetree[SubScript] = {Left, Right, 0, 0};
        } else {
            Linetree[SubScript] = {Left, Right, 0, 0};
            int mid = (Left + Right) >> 1;
            build(SubScript<<1, Left, mid);
            build(SubScript<<1|1, mid+1, Right);
            pushUp(SubScript);
        }
    }
    
    T query(int Subscript, int Left, int Right) {
        if(Left <= Linetree[Subscript].L && Linetree[Subscript].R <= Right) {
            return Linetree[Subscript].Value;
        }
        pushDown(Subscript);
        int mid = (Linetree[Subscript].L + Linetree[Subscript].R) >> 1;
        T res = 0;
        if(Left <= mid) res = query(Subscript<<1, Left, Right);
        if(Right > mid) res = merge(res, query(Subscript<<1|1, Left, Right));
        return res;
    }
    
    // 单点更新：在指定位置增加val
    void point_add(int Subscript, int pos, T val) {
        if(Linetree[Subscript].L == Linetree[Subscript].R) {
            Linetree[Subscript].Value += val;
            return;
        }
        pushDown(Subscript);
        int mid = (Linetree[Subscript].L + Linetree[Subscript].R) >> 1;
        if(pos <= mid) point_add(Subscript<<1, pos, val);
        else point_add(Subscript<<1|1, pos, val);
        pushUp(Subscript);
    }
    
    // 查找第k大元素的位置（从大到小排序）
    int findKthLargest(int Subscript, int k) {
        if(Linetree[Subscript].L == Linetree[Subscript].R) {
            return Linetree[Subscript].L;
        }
        pushDown(Subscript);
        int rightCount = Linetree[Subscript<<1|1].Value;
        if(rightCount >= k) {
            return findKthLargest(Subscript<<1|1, k);
        } else {
            return findKthLargest(Subscript<<1, k - rightCount);
        }
    }
    
    // 获取总元素个数
    T getTotalCount() {
        return Linetree[1].Value;
    }
    
    // 清空线段树
    void clear() {
        fill(Linetree.begin(), Linetree.end(), LT{0, 0, 0, 0});
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, minSalary;
    cin >> n >> minSalary;
    
    linetree<int> st(RANGE);
    st.build(1, 0, RANGE - 1);
    
    int globalAdd = 0; // 全局工资调整量
    int leftCount = 0; // 离职员工数
    
    for (int i = 0; i < n; i++) {
        char op;
        int k;
        cin >> op >> k;
        
        if (op == 'I') {
            // 插入新员工
            if (k >= minSalary) {
                int relativeSalary = k - globalAdd; // 相对于当前基准的工资
                int pos = relativeSalary + OFFSET;
                if (pos >= 0 && pos < RANGE) {
                    st.point_add(1, pos, 1);
                }
            }
        } else if (op == 'A') {
            // 全体加工资
            globalAdd += k;
        } else if (op == 'S') {
            // 全体减工资
            globalAdd -= k;
            
            // 移除工资低于最低标准的员工
            int threshold = minSalary - globalAdd + OFFSET;
            if (threshold > 0) {
                int leavingCount = st.query(1, 0, min(threshold - 1, RANGE - 1));
                leftCount += leavingCount;
                
                // 重建线段树，只保留工资不低于最低标准的员工
                vector<pair<int, int>> remaining; // {position, count}
                for (int j = max(0, threshold); j < RANGE; j++) {
                    int count = st.query(1, j, j);
                    if (count > 0) {
                        remaining.push_back({j, count});
                    }
                }
                
                st.clear();
                st.build(1, 0, RANGE - 1);
                for (auto& p : remaining) {
                    st.point_add(1, p.first, p.second);
                }
            }
        } else if (op == 'F') {
            // 查询第k高工资
            int totalEmployees = st.getTotalCount();
            if (k > totalEmployees) {
                cout << -1 << "\n";
            } else {
                // 找第k高工资
                int pos = st.findKthLargest(1, k);
                int actualSalary = pos - OFFSET + globalAdd;
                cout << actualSalary << "\n";
            }
        }
    }
    
    cout << leftCount << "\n";
    
    return 0;
}