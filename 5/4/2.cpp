#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring> // for memset

using namespace std;

typedef long long ll;

ll N;
string S;
ll memo[65][65][2];
const ll MOD = 10000007;

// 数位DP函数
// pos: 当前处理的二进制位（从左到右，0-indexed）
// count: 还需要放置的1的数量
// is_less: 当前前缀是否已经小于N的前缀
ll dp(int pos, int count, bool is_less) {
    // 如果1已经用完或者超过了，或者位数已经填满
    if (count < 0) return 0;
    if (pos == S.length()) {
        return count == 0;
    }
    // 记忆化搜索
    if (memo[pos][count][is_less] != -1) {
        return memo[pos][count][is_less];
    }

    ll ans = 0;
    // 确定当前位能填的上限
    int upper_bound = is_less ? 1 : (S[pos] - '0');

    // 遍历当前位可以填的数字 (0 或 1)
    for (int digit = 0; digit <= upper_bound; ++digit) {
        ans += dp(pos + 1, count - digit, is_less || (digit < upper_bound));
    }

    return memo[pos][count][is_less] = ans;
}

// 快速幂函数，计算 (base^exp) % mod
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    // 将N转换为二进制字符串
    ll temp_n = N;
    if (temp_n == 0) {
        S = "0";
    } else {
        while (temp_n > 0) {
            S += (temp_n % 2) + '0';
            temp_n /= 2;
        }
        reverse(S.begin(), S.end());
    }

    ll total_product = 1;
    int max_popcount = S.length();

    // 遍历所有可能的popcount值 k
    for (int k = 1; k <= max_popcount; ++k) {
        memset(memo, -1, sizeof(memo));
        // dp(0, k, false) 计算的是 [0, N] 中有k个1的数的数量。
        // 因为k>=1, popcount(0)=0 不会影响结果。
        ll count_k = dp(0, k, false);

        if (count_k > 0) {
            ll term = power(k, count_k);
            total_product = (total_product * term) % MOD;
        }
    }

    cout << total_product << endl;

    return 0;
}