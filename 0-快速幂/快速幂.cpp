#include <cstdio>
#include <cmath>
using namespace std;

// 最简单的幂运算，直接循环计算
// 注意：这种方法效率极低，通常不适用于大数的幂运算
int pow_0(int x, int n)
{
    int res = 1;
    for (int i = 0; i < n; i++)
        res *= x;
    return res;
}


// 快速幂运算，时间复杂度 O(log n)
// 通过二进制位的方式来计算幂
int pow_1(int x, int n)
{
    int res = 1;
    for (int i = 0; i < 32; ++i)
    {
        // n 在第 i 位上为 1，则将 res 乘以 x 的 (2^i) 次方
        if ((1 << i) & n) {
            res = res * x;
        }
        // 每次循环将 x 平方，也就是在每次循环中将 x 置为初始值的 (2^i) 次方
        x = x * x;
    }
    return res;
}

// 也可以写成另一种循环风格
// 同样是从低位到高位处理，只不过我们每次将 n 右移一位
// 好处在于我们不需要人工处理第 i 位的上限，直接通过最后 n == 0 来结束循环
int pow_2(int x, int n)
{
    int res = 1;
    while (n) {
        if (n & 1) res = res * x;
        x = x * x;
        n >>= 1;
    }
    return res;
}


// 通常快速幂会用在模运算中
// 这里是一个模快速幂的实现
// 计算 (x^n) % mod
// 注意：这里的 x, n, mod 都是 long long 类型
typedef long long ll;
ll Qpow(ll x, ll n, ll mod)
{
    ll res = 1;
    x %= mod;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

ll Qpow0(ll x, ll n, ll mod)
{
    if (n == 0) return 1; // 任何数的 0 次方都是 1
    ll res = Qpow0(x, n / 2, mod);
    if (n % 2 == 1)
        return res * res % mod * x % mod; // 如果 n 是奇数，则需要额外乘以 x
    else
        return res * res % mod; // 如果 n 是偶数，则直接平方结果
}

int main()
{
    printf("pow(2, 10) = %d\n", pow(2, 10)); // 使用标准库的 pow 函数
    printf("pow(2, 10) = %d\n", (int)pow(2, 10)); // 使用标准库的 pow 函数
    // 标准库的 pow 函数返回的是 double 类型，可能会有精度问题
    printf("pow_0(2, 10) = %d\n", pow_0(2, 10));
    printf("pow_1(2, 10) = %d\n", pow_1(2, 10));
    printf("pow_2(2, 10) = %d\n", pow_2(2, 10));
    printf("Qpow(2, 10, 1000) = %lld\n", Qpow(2, 10, 1000));
    printf("Qpow(2, 20, 1000) = %lld\n", Qpow(2, 20, 1000));
    printf("Qpow(2, 1e9 + 7, 1000) = %lld\n", Qpow(2, 1000000007, 1000));
}