
## 🔹 一、基本概念（适用于排序后）

| 函数                                 | 含义              |
| ---------------------------------- | --------------- |
| `lower_bound(a + 1, a + n + 1, x)` | 找第一个 **≥x** 的位置 |
| `upper_bound(a + 1, a + n + 1, x)` | 找第一个 **>x** 的位置 |

返回值是一个指针，要得到**下标**，可以减去起始地址：

```cpp
int pos = lower_bound(a, a + n, x) - a;
```

---

## 🔹 二、使用前提：必须先排序！

这两个函数只能在**有序序列**上使用。

```cpp
sort(a, a + n); // 数组排序
sort(vec.begin(), vec.end()); // vector 排序
sort(vec.begin() + 1, vec.end());
```

---

## 🔹 三、数组 vs vector 的使用方式

### ✅ 普通数组（a[0..n-1]）

```cpp
int pos = lower_bound(a, a + n, x) - a;
```

### ✅ vector（vec[0..n-1]）

```cpp
int pos = lower_bound(vec.begin(), vec.end(), x) - vec.begin();
```

或者更清晰写法：

```cpp
auto it = lower_bound(vec.begin(), vec.end(), x);
int pos = it - vec.begin();
```

---

## 🔹 四、下标从 1 开始的情况（如 a[1..n]）

算法竞赛中同样习惯让数组从下标 1 开始：

```cpp
sort(a + 1, a + n + 1); // 排序 a[1..n]
int pos = lower_bound(a + 1, a + n + 1, x) - a; // 得到的是真实下标
```

例如：

```cpp
int a[] = {0, 1, 3, 3, 5, 7}; // a[1..5]
int n = 5;

int pos = lower_bound(a + 1, a + n + 1, 3) - a;
// pos = 2，即第一个 ≥3 的下标是 2
```

同样地，用于 `vector` 时也可以控制范围（但不太常见）：

```cpp
vector<int> vec(n + 1);
for (int i = 1; i <= n; ++i)
	cin >> vec[i];
sort(vec.begin() + 1, vec.end());
int pos = lower_bound(vec.begin() + 1, vec.end(), 3) - vec.begin();
```

---

## 🔹 五、配合 sort + unique 实现离散化

常用于压缩数值范围（如坐标压缩、树状数组输入预处理）。

### ✅ 示例（数组）

```cpp
int b[MAXN]; // 原始数据
int c[MAXN]; // 用于离散化的数组

for (int i = 1; i <= n; ++i)
    c[i] = b[i];

sort(c + 1, c + n + 1);
int m = unique(c + 1, c + n + 1) - (c + 1); // m 是去重后的元素个数

for (int i = 1; i <= n; ++i)
    b[i] = lower_bound(c + 1, c + m + 1, b[i]) - c; // 映射到 [1, m]
```

### ✅ 示例（vector）

```cpp
vector<int> vec = {5, 3, 7, 3, 9};

vector<int> disc = vec;
sort(disc.begin(), disc.end());
disc.erase(unique(disc.begin(), disc.end()), disc.end());

for (int &x : vec)
    x = lower_bound(disc.begin(), disc.end(), x) - disc.begin() + 1;
```

---

| 操作 | 数组写法 | vector 写法 |
|------|----------|--------------|
| lower_bound | `lower_bound(a, a + n, x) - a` | `lower_bound(vec.begin(), vec.end(), x) - vec.begin()` |
| upper_bound | `upper_bound(a, a + n, x) - a` | `upper_bound(vec.begin(), vec.end(), x) - vec.begin()` |
| 下标从 1 开始 | `lower_bound(a + 1, a + n + 1, x) - a` | 控制 begin+1 即可 |
| 离散化 | `sort + unique + lower_bound` | 同理，注意 vector 范围操作 |
