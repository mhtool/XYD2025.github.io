#include <bits/stdc++.h>
using namespace std;

struct HashTable
{
    int n;
    vector<vector<int>> ids; // 哈希表里面出现哪些元素
    vector<int> cnt, val;
    int id_cnt;
    
    HashTable(int _n) : n(_n), ids(_n), cnt(_n + 1), val(_n + 1), id_cnt(0) {}
    
    int get_hash(int x)
    {
        x = x << 1 | x << 14 ^ (x >> 2) & (x >> 3);
        x = x * x + 1 % n;
        x = (x % n + n) % n;
        return x;
    }
    
    int find_id(int x)
    {
        int pos = get_hash(x);
        for (int i : ids[pos])
        {
            if (val[i] == x)
                return i;
        }
        ids[pos].push_back(++id_cnt); // 如果哈希表里面没有这个元素，就插入 连地址法
        val[id_cnt] = x;
        return id_cnt;
    }

    vector<pair<int, int>> get_ans()
    {
        vector<pair<int, int>> ans;
        for (int i = 1; i <= id_cnt; ++i)
            ans.emplace_back(val[i], cnt[i]);
        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    
    HashTable ht(n);

    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        int id = ht.find_id(x);
        ++ht.cnt[id];
    }
    auto ans = ht.get_ans();    
    for (auto [x, c] : ans)
        cout << x << " " << c << endl;
}