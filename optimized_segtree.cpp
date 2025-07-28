#include<bits/stdc++.h>
using namespace std;

const int OFFSET = 100000;
const int MAXN = 200005;

int tree[MAXN << 2];
int n, mnn, adder, goman;

void update(int o, int l, int r, int pos, int val) {
    if (l == r) {
        tree[o] += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(o << 1, l, mid, pos, val);
    else update(o << 1 | 1, mid + 1, r, pos, val);
    tree[o] = tree[o << 1] + tree[o << 1 | 1];
}

int query(int o, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) return tree[o];
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query(o << 1, l, mid, ql, qr);
    if (qr > mid) res += query(o << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int findKth(int o, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int rightCnt = tree[o << 1 | 1];
    if (rightCnt >= k) return findKth(o << 1 | 1, mid + 1, r, k);
    else return findKth(o << 1, l, mid, k - rightCnt);
}

void clear() {
    memset(tree, 0, sizeof(tree));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> mnn;
    
    for (int i = 0; i < n; i++) {
        char opt;
        int k;
        cin >> opt >> k;
        
        if (opt == 'I') {
            if (k >= mnn) {
                int pos = k - adder + OFFSET;
                if (pos >= 0 && pos < MAXN) {
                    update(1, 0, MAXN - 1, pos, 1);
                }
            }
        } else if (opt == 'A') {
            adder += k;
        } else if (opt == 'S') {
            adder -= k;
            int threshold = mnn - adder + OFFSET;
            
            if (threshold > 0) {
                int leaving = query(1, 0, MAXN - 1, 0, min(threshold - 1, MAXN - 1));
                goman += leaving;
                
                if (leaving > 0) {
                    // 快速重建：只保存必要的信息
                    vector<pair<int, int>> keep;
                    for (int j = max(0, threshold); j < MAXN; j++) {
                        int cnt = query(1, 0, MAXN - 1, j, j);
                        if (cnt > 0) keep.push_back({j, cnt});
                    }
                    
                    clear();
                    for (auto& p : keep) {
                        update(1, 0, MAXN - 1, p.first, p.second);
                    }
                }
            }
        } else if (opt == 'F') {
            int total = tree[1];
            if (k > total) {
                cout << -1 << '\n';
            } else {
                int pos = findKth(1, 0, MAXN - 1, k);
                cout << pos - OFFSET + adder << '\n';
            }
        }
    }
    
    cout << goman << '\n';
    return 0;
}