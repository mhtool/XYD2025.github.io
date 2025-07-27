#include <bits/stdc++.h>

using namespace std;

// B 的最大值为 100000，数组大小需要至少为 100001
const int MAX_B = 100001;

// 并查集的父节点数组
int parent[MAX_B + 1];
// 筛法使用的数组，is_not_prime[i]为true表示i是合数
bool is_not_prime[MAX_B + 1];
// 存储找到的质数
vector<int> primes;

/**
 * @brief DSU查找操作（带路径压缩）
 * @param v 要查找的元素
 * @return 元素v所在集合的代表元
 */
int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }
    // 路径压缩
    return parent[v] = find_set(parent[v]);
}

/**
 * @brief DSU合并操作
 * @param a 第一个元素
 * @param b 第二个元素
 * @return 如果两个元素原先不在同一集合（成功合并），返回true，否则返回false
 */
bool unite_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        // 简单的合并策略，可以将b集合合并到a集合
        parent[b] = a;
        return true;
    }
    return false;
}

/**
 * @brief 埃拉托斯特尼筛法，找出所有小于等于n的质数
 * @param n 上限
 */
void sieve(int n) {
    is_not_prime[0] = is_not_prime[1] = true;
    for (int p = 2; p <= n; ++p) {
        if (!is_not_prime[p]) {
            primes.push_back(p);
            // 从 p*p 开始标记，因为小于 p*p 的 p 的倍数已经被更小的质数标记过了
            for (long long j = (long long)p * p; j <= n; j += p) {
                is_not_prime[j] = true;
            }
        }
    }
}

int main() {
    // 使用C++流进行快速I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, p_min;
    cin >> a >> b >> p_min;

    // 初始时，有 B - A + 1 个笼子
    int num_cages = b - a + 1;

    // 初始化并查集，让1到b每个数都成为自己的父节点
    // std::iota 可以方便地完成这个初始化
    iota(parent + 1, parent + b + 1, 1);

    // 预处理，找出所有小于等于 b 的质数
    sieve(b);

    // 使用二分查找找到第一个大于等于 p_min 的质数，从它开始遍历
    auto it = lower_bound(primes.begin(), primes.end(), p_min);

    // 遍历所有符合 P 条件的质数
    for (; it != primes.end(); ++it) {
        int p = *it;

        // 找到区间 [a, b] 内 p 的第一个倍数
        // (a + p - 1) / p 是向上取整的技巧
        long long first_multiple = (long long)(a + p - 1) / p * p;
        
        // 如果第一个倍数已经超出b，那么这个质数在区间内没有两个或以上倍数
        if (first_multiple > b) {
            continue;
        }

        // 遍历 p 在区间 [a, b] 内的其它倍数，并将它们与第一个倍数合并
        for (long long j = first_multiple + p; j <= b; j += p) {
            if (unite_sets(first_multiple, j)) {
                // 每成功合并一次，笼子总数减一
                num_cages--;
            }
        }
    }

    cout << num_cages << endl;

    return 0;
}