
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // 在处理大量输入输出时，这两行可以显著提高程序性能
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.length();

    // 题目给的查询区间是 1-indexed, C++ 字符串是 0-indexed。
    // 我们使用 n+1 大小的前缀和数组，pref[i] 存储 s[0...i-1] 的信息，
    // 这样查询 [l, r] 时，可以方便地使用 pref[r] 和 pref[l-1]。

    // 使用 long long 防止中间计算结果溢出，因为 N 最大可达 200000
    vector<long long> cnt_g(n + 1, 0);
    vector<long long> cnt_c(n + 1, 0);
    vector<long long> cnt_d(n + 1, 0);

    vector<long long> cnt_gc(n + 1, 0);  // s[0...i-1] 中 "gc" 子序列的数量
    vector<long long> cnt_cd(n + 1, 0);  // s[0...i-1] 中 "cd" 子序列的数量
    vector<long long> cnt_gcd(n + 1, 0); // s[0...i-1] 中 "gcd" 子序列的数量

    // 预处理步骤, 时间复杂度 O(n)
    for (int i = 0; i < n; ++i) {
        // 先继承前一个位置的值
        cnt_g[i + 1] = cnt_g[i];
        cnt_c[i + 1] = cnt_c[i];
        cnt_d[i + 1] = cnt_d[i];
        cnt_gc[i + 1] = cnt_gc[i];
        cnt_cd[i + 1] = cnt_cd[i];
        cnt_gcd[i + 1] = cnt_gcd[i];

        // 根据当前字符 s[i] 更新计数值
        if (s[i] == 'g') {
            cnt_g[i + 1]++;
        } else if (s[i] == 'c') {
            cnt_c[i + 1]++;
            // 新的 'c' 可以和之前所有的 'g' 组成 "gc"
            cnt_gc[i + 1] += cnt_g[i];
        } else if (s[i] == 'd') {
            cnt_d[i + 1]++;
            // 新的 'd' 可以和之前所有的 'c' 组成 "cd"
            cnt_cd[i + 1] += cnt_c[i];
            // 新的 'd' 可以和之前所有的 "gc" 子序列组成 "gcd"
            cnt_gcd[i + 1] += cnt_gc[i];
        }
    }

    int q;
    cin >> q;

    // 题目要求对 2^31 取模
    const long long mod = 1LL << 31;

    while (q--) {
        int l, r;
        cin >> l >> r; // 1-indexed 查询

        // 获取 s[0...l-2] (即 l-1 位置) 的各项计数值
        long long g_before = cnt_g[l - 1];
        long long c_before = cnt_c[l - 1];
        long long gcd_before = cnt_gcd[l - 1];
        long long gc_before = cnt_gc[l - 1];
        long long cd_before = cnt_cd[l - 1];

        // 获取 s[l-1...r-1] 区间内的 'd' 的数量
        long long d_in_range = cnt_d[r] - cnt_d[l - 1];
        
        // 计算 s[l-1...r-1] 区间内的 "cd" 子序列数量
        // = (s[0..r-1]中的"cd") - (s[0..l-2]中的"cd") - (s[0..l-2]的'c'与s[l-1..r-1]的'd'组成的"cd")
        long long cd_in_range = cnt_cd[r] - cd_before - (c_before * d_in_range);

        // 计算 s[l-1...r-1] 区间内的 "gcd" 子序列数量 (容斥原理)
        // = (s[0..r-1]中的"gcd") - (s[0..l-2]中的"gcd")
        //   - (s[0..l-2]的"gc"与s[l-1..r-1]的'd'组成的"gcd")
        //   - (s[0..l-2]的'g'与s[l-1..r-1]的"cd"组成的"gcd")
        long long ans = cnt_gcd[r] - gcd_before;
        ans -= gc_before * d_in_range;
        ans -= g_before * cd_in_range;

        // 因为 ans 可能为负，取模需要特殊处理
        cout << (ans % mod + mod) % mod << endl;
    }
    return 0;
}
